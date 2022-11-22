import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {OwnerDTO} from "../../../Model/ownerDTO";

@Component({
  selector: 'owners-modal',
  templateUrl: './owners-modal.component.html',
  styleUrls: ['./owners-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class OwnersModalComponent {
  inputId: string | null = null;
  inputFirstName: string | null = null;
  inputLastName: string | null = null;
  inputEmail: string | null = null;
  inputPhoneNumber: string | null = null;
  inputDateOfBirth: string | null = null;

  constructor(public modalRef: MdbModalRef<OwnersModalComponent>) {
  }

  close(): void {
    this.modalRef.close("Modal was closed");
  }

  submitInformation(): void {
    this.modalRef.close({
      id: this.inputId,
      firstName: this.inputFirstName,
      lastName: this.inputLastName,
      email: this.inputEmail,
      phoneNumber: this.inputPhoneNumber,
      dateOfBirth: this.inputDateOfBirth
    });
  }
}
