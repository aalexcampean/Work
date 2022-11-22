import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';

@Component({
    selector: 'article-modal',
    templateUrl: './article-modal.component.html',
    styleUrls: ['./article-modal.component.css']
})
export class ArticleModalComponent {
    inputUserName: string | null = null;
    inputSummary: string | null = null;
    inputJournalName: string | null = null;

    constructor(public modalRef: MdbModalRef<ArticleModalComponent>) {
    }

    close(): void {
        this.modalRef.close("Modal was closed");
    }

    submitInformation(): void {
        this.modalRef.close({
            userName: this.inputUserName,
            summary: this.inputSummary,
            journalName: this.inputJournalName
        });
    }
}
