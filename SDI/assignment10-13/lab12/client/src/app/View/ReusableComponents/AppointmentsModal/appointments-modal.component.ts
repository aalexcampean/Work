import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {AppointmentDTO} from "../../../Model/appointmentDTO";

@Component({
  selector: 'appointments-modal',
  templateUrl: './appointments-modal.component.html',
  styleUrls: ['./appointments-modal.component.css', "../../ReusableComponents/ReusableStyling/ModalStyling.css", "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class AppointmentsModalComponent {
  appointments: Array<AppointmentDTO> = []

  constructor(public modalRef: MdbModalRef<AppointmentsModalComponent>) {
  }

  public close(): void {
    this.modalRef.close("Modal was closed");
  }
}
