SELECT count(*) as 'No. of movies' FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10);
