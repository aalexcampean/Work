package web.controller;

import core.dto.ArticleDTO;
import core.dto.ArticlesDTO;
import core.dto.ReceiveArticleDTO;
import core.service.IJournalService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.stream.Collectors;

@RestController
public class JournalController {
    // Dependencies
    @Autowired
    private IJournalService journalService;

    @RequestMapping(value = "/articles/user/{username}")
    ArticlesDTO getUserJournals(@PathVariable String username) {
        return new ArticlesDTO(journalService.getUserArticles(username)
                .stream()
                .map(article -> new ArticleDTO().encode(article))
                .collect(Collectors.toSet()));
    }

    @RequestMapping(value = "/articles/user/{username}/{journalName}")
    ArticlesDTO getUserArticlesByName(@PathVariable String username, @PathVariable String journalName) {
        return new ArticlesDTO(journalService.getUserArticlesByJournalName(username, journalName)
                .stream()
                .map(article -> new ArticleDTO().encode(article))
                .collect(Collectors.toSet()));
    }

    @RequestMapping(value = "/articles", method = RequestMethod.POST)
    void addArticle(@RequestBody ReceiveArticleDTO articleDTO) {
        journalService.addArticle(articleDTO);
    }
}
