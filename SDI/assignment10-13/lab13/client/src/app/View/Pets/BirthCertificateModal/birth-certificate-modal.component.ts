import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {OwnerDTO} from "../../../Model/ownerDTO";
import {PetDTO} from "../../../Model/petDTO";

@Component({
  selector: 'birth-certificate-modal',
  templateUrl: './birth-certificate-modal.component.html',
  styleUrls: ['./birth-certificate-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class BirthCertificateModalComponent {
  gradeOptions = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
  pets: Array<PetDTO> = [];
  showPets: boolean = false;
  inputId: string | null = null;
  inputText: string | null = null;
  inputLocation: string | null = null;
  inputDate: string | null = null;
  inputHealthGrade: string | null = null;
  inputPetId: string | null = null;

  constructor(public modalRef: MdbModalRef<BirthCertificateModalComponent>) {
  }

  public close(): void {
    this.modalRef.close("Modal was closed");
  }

  submitInformation(): void {
    this.modalRef.close({
      id: this.inputId,
      text: this.inputText,
      location: this.inputLocation,
      date: this.inputDate,
      healthGrade: this.inputHealthGrade,
      petId: this.inputPetId
    });
  }
}
