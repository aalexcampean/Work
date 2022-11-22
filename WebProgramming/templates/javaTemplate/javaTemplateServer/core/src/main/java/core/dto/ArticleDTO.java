package core.dto;

import core.entity.Article;
import lombok.*;

import java.text.SimpleDateFormat;
import java.util.Date;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Getter
@Setter
@EqualsAndHashCode
@ToString(callSuper = true)
public class ArticleDTO {
    private int id;
    private String userName;
    private int journalId;
    private String summary;
    private String date;

    public ArticleDTO encode(Article article) {
        SimpleDateFormat DateFor = new SimpleDateFormat("dd/MM/yyyy");
        String stringDate= DateFor.format(article.getDate());
        return new ArticleDTO(article.getId(),
                article.getUserName(),
                article.getJournal().getId(),
                article.getSummary(),
                stringDate);
    }
}
