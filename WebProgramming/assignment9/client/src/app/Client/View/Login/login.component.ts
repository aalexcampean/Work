import {Component, Input, OnInit} from '@angular/core';
import {DocumentDTO} from "../../Model/documentDTO";
import {DocumentsController} from "../../Controller/document-service";
import {DocumentsModalComponent} from "../DocumentsModal/documents-modal.component";
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";

@Component({
  selector: 'login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit{
  userNameInput = "";
  passwordInput = "";

  constructor(private documentController: DocumentsController) {
  }

  ngOnInit(): void {
  }

  onLogin(): void {

  }
}
