import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {DocumentDTO} from "../../Model/DocumentDTO";

@Component({
  selector: 'documents-modal',
  templateUrl: './documents-modal.component.html',
  styleUrls: ['./documents-modal.component.css']
})
export class DocumentsModalComponent {
  formatOptions: any;
  inputId: number | null = null;
  inputTitle: string | null = null;
  inputAuthor: string | null = null;
  inputNoPages: number | null = null;
  inputType: string | null = null;
  inputFormat: string | null = null;

  constructor(public modalRef: MdbModalRef<DocumentsModalComponent>) {
  }

  close(): void {
    this.modalRef.close("Modal was closed");
  }

  submitInformation(): void {
    this.modalRef.close({
      id: this.inputId,
      title: this.inputTitle,
      author: this.inputAuthor,
      noOfPages: this.inputNoPages,
      type: this.inputType,
      format: this.inputFormat
    });
  }
}
