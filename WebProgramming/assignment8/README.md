# Assignment8

Develop a web application based on JSP (Java Server Pages) or Java Servlets.
All web pages should be accessible only if the user logs in using a username and a password (create a session each time a user logs in, and destroy the session when the user logs out). Have in mind the user experience when you implement the problem:

add different validation logic for input fields
do not force the user to input an ID for an item if he wants to delete/edit/insert it; this should happen automatically (e.g. the user clicks an item from a list, and a page/modal prepopulated with the data for that particular item is opened, where the user can edit it)
add confirmation when the user deletes/cancels an item
do a bare minimum CSS that at least aligns the various input fields


Solve the following problem using the JSP/Servlet technology. State information (between web requests) is always stored in a database; you may store some state information in cookies/session objects. Write a web application for a forum. Users must identify themselfs prior to entering the forum. Each user can start a new topic or can comment (post) on an existing topic. Each user must be able to delete its own posts (comments). The posts of a topic should be displayed in a single web page.
