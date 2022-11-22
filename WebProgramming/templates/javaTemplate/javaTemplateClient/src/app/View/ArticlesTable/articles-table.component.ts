import {Component, Input, OnInit} from '@angular/core';
import {ArticleDTO, ArticlesDTO} from "../../Model/articleDTO";
import {ArticleService} from "../../Service/article.service";
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {ArticleModalComponent} from "../ArticlesModal/article-modal.component";
import {SendArticleDTO} from "../../Model/sendArticleDTO";

@Component({
    selector: 'articles-table',
    templateUrl: './articles-table.component.html',
    styleUrls: ['./articles-table.component.css']
})
export class ArticlesTableComponent implements OnInit {
    title = 'Subscriptions';
    articles: Array<ArticleDTO> = [];
    journalNameInput = "";
    currentUser = sessionStorage.getItem('username');
    modalArticleRef: MdbModalRef<ArticleModalComponent> | null = null;

    constructor(private articleService: ArticleService, private modalService: MdbModalService) {
    }

    ngOnInit(): void {
        this.getUserArticles();
    }

    getUserArticles(): void {
        this.articleService.getUserArticles(this.currentUser!)
            .subscribe(result => this.articles = result.articles);
    }

    getUserArticlesByJournalName(): void {
        this.articleService.getUserArticlesByJournalName(this.currentUser!, this.journalNameInput)
            .subscribe(articles => {
                this.articles = articles.articles;
            });
    }

    public addArticle(article: SendArticleDTO): void {
        this.articleService.addArticleToJournal(article);
    }

    public openModalForAdd(): void {
        this.modalArticleRef = this.modalService.open(ArticleModalComponent, {
            data: {
                inputUserName: this.currentUser
            },
            modalClass: 'modal-lg'
        });
        this.modalArticleRef.onClose.subscribe((response: SendArticleDTO | string) => {
            if (typeof response === "string") {
            } else {
                this.addArticle(response);
            }
        });
    }
}
