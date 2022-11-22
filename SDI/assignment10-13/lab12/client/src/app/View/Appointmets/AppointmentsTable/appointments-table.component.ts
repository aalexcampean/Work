import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {AppointmentService} from "../../../Controller/appointment-service";
import {AppointmentDTO} from "../../../Model/appointmentDTO";
import {AddUpdateAppointmentsModalComponent} from "../AddUpdateAppointmentsModal/add-update-appointments-modal.component";

@Component({
  selector: 'appointments-table',
  templateUrl: './appointments-table.component.html',
  styleUrls: ['./appointments-table.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class AppointmentsTableComponent implements OnInit{
  appointments: Array<AppointmentDTO> = [];
  modalAddUpdateRef: MdbModalRef<AddUpdateAppointmentsModalComponent> | null = null;

  constructor(private appointmentService: AppointmentService, private modalAddUpdateService: MdbModalService) {
  }

  ngOnInit(): void {
    this.getAppointments();
  }

  public getAppointments(): void {
    this.appointmentService.getAllAppointments()
      .subscribe(appointments => this.appointments = appointments.appointments);
  }

  public addAppointment(appointment: AppointmentDTO): void {
    this.appointmentService.addAppointment(appointment);
    this.appointments.push(appointment);
  }

  public deleteOwner(id: number): void {
    this.appointmentService.deleteAppointment(id);
    this.appointments = this.appointments.filter((appointment) => appointment.id != id);
  }

  public updateOwner(appointment: AppointmentDTO): void {
    this.appointmentService.updateAppointment(appointment);
  }

  public openModalForAdd(): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(AddUpdateAppointmentsModalComponent, {
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: AppointmentDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.addAppointment(response);
      }
    });
  }

  public openModalForUpdate(appointment: AppointmentDTO): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(AddUpdateAppointmentsModalComponent, {
      data: {
        inputId: appointment.id,
        inputPetId: appointment.petId,
        inputVetId: appointment.vetId,
        inputType: appointment.type,
        inputDate: appointment.date
      },
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: AppointmentDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.updateOwner(response);
      }
    });
  }
}
