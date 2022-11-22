import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {AppointmentService} from "../../../Controller/appointment-service";
import {AppointmentDTO} from "../../../Model/appointmentDTO";
import {
  AddUpdateAppointmentsModalComponent
} from "../AddUpdateAppointmentsModal/add-update-appointments-modal.component";
import {PetDTO} from "../../../Model/petDTO";
import {VetDTO} from "../../../Model/vetDTO";
import {PetService} from "../../../Controller/pet-service";
import {VetService} from "../../../Controller/vet-service";
import {UntilDestroy, untilDestroyed} from "@ngneat/until-destroy";
import {tap} from "rxjs";

@UntilDestroy()
@Component({
  selector: 'appointments-table',
  templateUrl: './appointments-table.component.html',
  styleUrls: ['./appointments-table.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class AppointmentsTableComponent implements OnInit {
  appointments: Array<AppointmentDTO> = [];
  pets: Array<PetDTO> = [];
  vets: Array<VetDTO> = [];
  modalAddUpdateRef: MdbModalRef<AddUpdateAppointmentsModalComponent> | null = null;
  pageNumber = 1;
  pageSize = 5;
  count = 0;

  constructor(private appointmentService: AppointmentService, private petService: PetService, private vetService: VetService, private modalAddUpdateService: MdbModalService) {
  }

  ngOnInit(): void {
    this.getAppointments();
    this.getPets();
    this.getVets();
  }

  handlePageChange(event: any): void {
    this.pageNumber = event;
    this.ngOnInit();
  }

  public getAppointments(): void {
    this.appointmentService.getAllPaginatedAppointments(this.pageNumber, this.pageSize)
      .pipe(
        untilDestroyed(this),
        tap((appointments) => {
          this.appointments = appointments.appointments;
          this.count = appointments.total;
          this.appointments = this.appointments.sort((a, b) => a.id - b.id);
        })
      )
      .subscribe(appointments => this.appointments = appointments.appointments);
  }

  public getPets(): void {
    this.petService.getAllPets()
      .subscribe(pets => this.pets = pets.pets);
  }

  public getVets(): void {
    this.vetService.getAllVets()
      .subscribe(vets => this.vets = vets.vets);
  }

  public getPetNameAndBreed(id: number): String | null {
    const petDTO = this.pets.find(function (pet) {
      return pet.id === id;
    });

    if (petDTO != null) {
      return petDTO.name + " - " + petDTO.breed;
    }
    return null;
  }

  public getVetName(id: number): String | null {
    const vetDTO = this.vets.find(function (vet) {
      return vet.id === id;
    });

    if (vetDTO != null) {
      return vetDTO.firstName + " " + vetDTO.lastName;
    }
    return null;
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
      data: {
        pets: this.pets,
        vets: this.vets
      },
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
        pets: this.pets,
        vets: this.vets,
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
