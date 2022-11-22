package core.service;

import core.dto.ReceiveArticleDTO;
import core.entity.Article;

import java.util.List;

public interface IJournalService {
    List<Article> getUserArticles(String userName);
    List<Article> getUserArticlesByJournalName(String userName, String journalName);

    void addArticle(ReceiveArticleDTO articleDTO);
}
