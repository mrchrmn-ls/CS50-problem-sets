SELECT name FROM people WHERE id != (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958) -- exclude Kevin bacon
AND id IN (
SELECT person_id FROM stars WHERE movie_id IN ( -- connect stars with movies
SELECT id FROM movies WHERE id IN ( -- find movies
SELECT movie_id FROM stars WHERE person_id IN ( -- connect movies with star
SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958)))); -- find Kevin Bacon