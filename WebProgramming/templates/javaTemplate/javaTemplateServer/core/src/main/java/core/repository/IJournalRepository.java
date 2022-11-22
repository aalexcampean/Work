package core.repository;

import core.entity.Journal;
import org.springframework.data.jpa.repository.JpaRepository;

public interface IJournalRepository extends JpaRepository<Journal, Integer> {
    Journal getFirstByName(String journalName);
}
