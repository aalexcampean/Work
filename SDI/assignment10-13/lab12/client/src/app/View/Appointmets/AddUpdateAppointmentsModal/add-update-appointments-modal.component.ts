import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {OwnerDTO} from "../../../Model/ownerDTO";

@Component({
  selector: 'add-update-appointments-modal',
  templateUrl: './add-update-appointments-modal.component.html',
  styleUrls: ['./add-update-appointments-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class AddUpdateAppointmentsModalComponent {
  inputId: string | null = null;
  inputPetId: string | null = null;
  inputVetId: string | null = null;
  inputType: string | null = null;
  inputDate: string | null = null;

  constructor(public modalRef: MdbModalRef<AddUpdateAppointmentsModalComponent>) {
  }

  close(): void {
    this.modalRef.close("Modal was closed");
  }

  submitInformation(): void {
    this.modalRef.close({
      id: this.inputId,
      petId: this.inputPetId,
      vetId: this.inputVetId,
      type: this.inputType,
      date: this.inputDate
    });
  }
}
