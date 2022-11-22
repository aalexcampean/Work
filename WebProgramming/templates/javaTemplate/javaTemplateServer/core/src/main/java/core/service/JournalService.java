package core.service;

import core.dto.ReceiveArticleDTO;
import core.entity.Article;
import core.entity.Journal;
import core.repository.IArticleRepository;
import core.repository.IJournalRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.stream.Collectors;

@Service
public class JournalService implements IJournalService {
    @Autowired
    private IArticleRepository articleRepository;
    @Autowired
    private IJournalRepository journalRepository;

    @Override
    @Transactional
    public List<Article> getUserArticles(String userName) {
        return articleRepository.findAll()
                .stream()
                .filter(j -> j.getUserName().equals(userName))
                .collect(Collectors.toList());
    }

    @Override
    @Transactional
    public List<Article> getUserArticlesByJournalName(String userName, String journalName) {
        Journal journal = journalRepository.getFirstByName(journalName);
        return articleRepository.getArticleByJournal(journal)
                .stream()
                .filter(j -> j.getUserName().equals(userName))
                .collect(Collectors.toList());
    }

    @Override
    @Transactional
    public void addArticle(ReceiveArticleDTO articleDTO) {
        Journal journal = journalRepository.getFirstByName(articleDTO.getJournalName());
        if (journal == null) {
            Journal newJournal = new Journal(articleDTO.getJournalName());
            journalRepository.save(newJournal);
        }

        journal = journalRepository.getFirstByName(articleDTO.getJournalName());
        Article newArticle = new Article(articleDTO.getUserName(), journal, articleDTO.getSummary());
        articleRepository.save(newArticle);
    }
}
