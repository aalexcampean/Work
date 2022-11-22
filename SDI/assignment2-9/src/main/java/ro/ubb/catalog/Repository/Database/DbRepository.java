package ro.ubb.catalog.Repository.Database;

import ro.ubb.catalog.Domain.BaseEntity;
import ro.ubb.catalog.Repository.Repository;

import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Optional;

public abstract class DbRepository<ID, T extends BaseEntity<ID>> implements Repository<ID, T> {
    private final String url;
    private final String user;
    private final String password;

    DbRepository(String url, String user, String password) {
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /**
     * Connects to the database
     *
     * @param cmd
     * @return the prepared statement, using the given command
     * @throws SQLException
     */
    public PreparedStatement connect(String cmd) throws SQLException {
        var connection = DriverManager.getConnection(url, user, password);
        return connection.prepareStatement(cmd);
    }

    /**
     * Looks for an entity based on its id
     *
     * @param id must be not null.
     * @return the entity identified by the given id if it exists
     */
    public abstract Optional<T> findOne(ID id);

    /**
     * Retries all entities in the database
     *
     * @return all entities
     */
    public abstract Iterable<T> findAll();

    /**
     * Adds an entity to the database
     *
     * @param entity must not be null.
     * @return the newly added entity if it doesn't already exist
     */
    public abstract Optional<T> save(T entity);

    /**
     * Deletes an entity from the database
     *
     * @param id must not be null.
     * @return the just deleted entity if it exists
     */
    public abstract Optional<T> delete(ID id);

    /**
     * Updates an entity from the database
     *
     * @param entity must not be null.
     * @return the just updated entity if it exists
     */
    public abstract Optional<T> update(T entity);
}
