import {Component, Input, OnInit} from '@angular/core';
import {DocumentDTO} from "../../Model/documentDTO";
import {DocumentsController} from "../../Controller/document-service";
import {DocumentsModalComponent} from "../DocumentsModal/documents-modal.component";
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";

@Component({
  selector: 'documents-table',
  templateUrl: './documents-table.component.html',
  styleUrls: ['./documents-table.component.css']
})
export class DocumentsTableComponent implements OnInit{

  modalRef: MdbModalRef<DocumentsModalComponent> | null = null;
  title = 'hello-world';
  documents: Array<DocumentDTO> = [];
  formatOptions = [
    { name: "PDF", value: 1 },
    { name: "JPG", value: 2 },
    { name: "PNG", value: 3 }
  ]
  typeInput = "";
  formatInput = "";

  constructor(private documentController: DocumentsController, private modalService: MdbModalService) {
  }

  ngOnInit(): void {
    this.getDocuments();
  }

  openModalForAdd(): void {
    this.modalRef = this.modalService.open(DocumentsModalComponent, {
      data: {
        formatOptions: this.formatOptions
      }
    });
    this.modalRef.onClose.subscribe((response: DocumentDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.addDocument(response);
      }
    });
  }

  openModalForUpdate(document: DocumentDTO): void {
    this.modalRef = this.modalService.open(DocumentsModalComponent, {
      data: {
        formatOptions: this.formatOptions,
        inputId: document.id,
        inputTitle: document.title,
        inputAuthor: document.author,
        inputNoPages: document.numberOfPages,
        inputType: document.type,
        inputFormat: document.format
      }
    });
    this.modalRef.onClose.subscribe((response: DocumentDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.updateDocument(response);
      }
    });
  }

  getDocuments(): void {
    this.documentController.getAllFiles()
      .subscribe(documents => this.documents = documents);
  }

  getDocumentsByType(): void {
    this.documentController.getAllFilesByType(this.typeInput)
      .subscribe(documents => {
        this.documents = documents;
      });
  }

  getDocumentsByFormat(): void {
    this.documentController.getAllFilesByFormat(this.formatInput)
      .subscribe(documents => {
        this.documents = documents;
      });
  }

  addDocument(document: DocumentDTO): void {
    this.documentController.addFile(document);
    this.getDocuments();
  }

  deleteDocument(id: number): void {
    this.documentController.deleteFile(id);
    this.documents = this.documents.filter((document) => document.id != id);
  }

  updateDocument(document: DocumentDTO): void {
    this.documentController.updateFile(document);
    this.getDocuments();
  }
}
