package core.repository;

import core.entity.Article;
import core.entity.Journal;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface IArticleRepository extends JpaRepository<Article, Integer> {
    List<Article> getArticleByJournal(Journal inputJournal);
}
