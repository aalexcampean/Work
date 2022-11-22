import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {OwnerDTO} from "../../../Model/ownerDTO";

@Component({
  selector: 'add-update-pets-modal',
  templateUrl: './add-update-pets-modal.component.html',
  styleUrls: ['./add-update-pets-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class AddUpdatePetsModalComponent {
  owners: Array<OwnerDTO> = []
  inputId: string | null = null;
  inputSpecies: string | null = null;
  inputBreed: string | null = null;
  inputName: string | null = null;
  inputDateOfEnrolment: string | null = null;
  inputOwnerId: string | null = null;

  constructor(public modalRef: MdbModalRef<AddUpdatePetsModalComponent>) {
  }

  close(): void {
    this.modalRef.close("Modal was closed");
  }

  submitInformation(): void {
    this.modalRef.close({
      id: this.inputId,
      species: this.inputSpecies,
      breed: this.inputBreed,
      name: this.inputName,
      dateOfEnrolment: this.inputDateOfEnrolment,
      ownerId: this.inputOwnerId
    });
  }
}
