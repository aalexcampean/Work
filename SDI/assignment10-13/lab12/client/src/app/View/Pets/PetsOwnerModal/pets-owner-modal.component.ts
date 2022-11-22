import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {OwnerDTO} from "../../../Model/ownerDTO";

@Component({
  selector: 'pets-owner-modal',
  templateUrl: './pets-owner-modal.component.html',
  styleUrls: ['./pets-owner-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class PetsOwnerModalComponent {
  owner: OwnerDTO | null = null

  constructor(public modalRef: MdbModalRef<PetsOwnerModalComponent>) {
  }

  public close(): void {
    this.modalRef.close("Modal was closed");
  }
}
