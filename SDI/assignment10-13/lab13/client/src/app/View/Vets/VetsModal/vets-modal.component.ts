import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';

@Component({
  selector: 'vets-modal',
  templateUrl: './vets-modal.component.html',
  styleUrls: ['./vets-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class VetsModalComponent {
  ratingOption = [1, 2, 3, 4, 5];
  inputId: string | null = null;
  inputFirstName: string | null = null;
  inputLastName: string | null = null;
  inputEmail: string | null = null;
  inputPhoneNumber: string | null = null;
  inputDateOfBirth: string | null = null;
  inputSalary: string | null = null;
  inputRating: string | null = null;

  constructor(public modalRef: MdbModalRef<VetsModalComponent>) {
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
      dateOfBirth: this.inputDateOfBirth,
      salary: this.inputSalary,
      rating: this.inputRating
    });
  }
}
