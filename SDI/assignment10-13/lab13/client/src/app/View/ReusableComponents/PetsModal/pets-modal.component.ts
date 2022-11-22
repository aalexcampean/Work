import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {PetDTO} from "../../../Model/petDTO";

@Component({
  selector: 'owner-pets-modal',
  templateUrl: './pets-modal.component.html',
  styleUrls: ['./pets-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class PetsModalComponent {
  pets: Array<PetDTO> = []

  constructor(public modalRef: MdbModalRef<PetsModalComponent>) {
  }

  public close(): void {
    this.modalRef.close("Modal was closed");
  }
}
