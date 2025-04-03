import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    total_investment = db.execute(
        "SELECT SUM(Shares * Price) as Invested FROM purchase WHERE id = ? AND Shares > 0", session["user_id"])
    return_of_inv = db.execute(
        "SELECT SUM(-(Shares * Price)) as ROI FROM purchase WHERE id = ? AND Shares < 0", session["user_id"])
    credited_amount = db.execute("SELECT cash FROM users WHERE id = ?",
                                 session["user_id"])[0]["cash"]

    if (not total_investment[0]["Invested"]):
        total_investment[0]["Invested"] = 0

    if (not return_of_inv[0]["ROI"]):
        return_of_inv[0]["ROI"] = 0

    cash_left = credited_amount - total_investment[0]["Invested"] + return_of_inv[0]["ROI"]

    purchase = db.execute(
        "SELECT Symbol, SUM(Shares) as Shares FROM purchase WHERE id = ? GROUP BY Symbol", session["user_id"])

    current_value = 0

    for stocks in purchase:
        current_value += stocks["Shares"] * lookup(stocks["Symbol"])["price"]

    return render_template("index.html", purchase=purchase, lookup=lookup, cash_left=cash_left, usd=usd, current_value=current_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if (request.method == "POST"):

        stock = lookup(request.form.get("symbol"))

        total_investment = db.execute(
            "SELECT SUM(Shares * Price) as Invested FROM purchase WHERE id = ? AND Shares > 0", session["user_id"])
        return_of_inv = db.execute(
            "SELECT SUM(-(Shares * Price)) as ROI FROM purchase WHERE id = ? AND Shares < 0", session["user_id"])
        credited_amount = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        if (not total_investment[0]["Invested"]):
            total_investment[0]["Invested"] = 0

        if (not return_of_inv[0]["ROI"]):
            return_of_inv[0]["ROI"] = 0
        cash_left = credited_amount - total_investment[0]["Invested"] + return_of_inv[0]["ROI"]
        if (not lookup(request.form.get("symbol"))):
            return apology("Missing Symbol")
        elif (not request.form.get("shares")):
            return apology("Missing Shares")

        elif (request.form.get("shares")):
            try:
                int(request.form.get("shares"))
            except ValueError:
                return apology("Invalid Share")

            if (int(request.form.get("shares")) < 1):
                return apology("Invalid Share")

        elif (int(request.form.get("shares")) * lookup(request.form.get("symbol"))["price"] > cash_left):
            return apology("CAN'T AFFORD")

        db.execute("INSERT INTO purchase (id, Symbol, Shares, Price, Transacted) VALUES (?, ?, ?, ?, DATETIME('now'))",
                   session["user_id"], request.form.get("symbol").upper(), request.form.get("shares"), stock["price"])

        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transaction = db.execute(
        "SELECT Symbol, Shares, Price, Transacted FROM purchase WHERE id = ?", session["user_id"])
    return render_template("history.html", transaction=transaction, usd=usd, lookup=lookup)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if (request.method == "POST"):
        if (not lookup(request.form.get("symbol"))):
            return apology("Invalid Symbol")
        stock = lookup(request.form.get("symbol"))
        return render_template("quoted.html", stock=stock, usd=usd)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password does not match", 400)

        # Checking whether or not user already exists.
        for username in db.execute("SELECT username from users"):
            if (request.form.get("username") == username["username"]):
                return apology("User already exists", 400)

        # Query database for username
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            request.form.get("username"), generate_password_hash(request.form.get("password"), method='scrypt', salt_length=16))

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if (request.method == "POST"):

        if (not request.form.get("symbol")):
            return apology("Select the stock")

        else:
            available_shares = db.execute(
                "SELECT SUM(Shares) AS Total_Shares FROM purchase WHERE id = ? AND Symbol = ?", session["user_id"], request.form.get("symbol"))
            if (available_shares[0]["Total_Shares"] < int(request.form.get("shares"))):
                return apology("Insufficient Shares")

            stock = lookup(request.form.get("symbol"))
            db.execute("INSERT INTO purchase (id, Symbol, Shares, Price, Transacted) VALUES (?, ?, -?, ?, DATETIME('now'))",
                       session["user_id"], request.form.get("symbol").upper(), request.form.get("shares"), stock["price"])

            flash("Sold!")
            return redirect("/")

    else:
        purchase = db.execute(
            "SELECT Symbol, SUM(Shares) AS Shares FROM purchase WHERE id = ? GROUP BY Symbol", session["user_id"])

        return render_template("sell.html", purchase=purchase)
