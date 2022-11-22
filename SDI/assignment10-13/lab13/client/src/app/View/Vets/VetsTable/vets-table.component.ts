import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef, MdbModalService} from "mdb-angular-ui-kit/modal";
import {VetService} from "../../../Controller/vet-service";
import {VetDTO} from "../../../Model/vetDTO";
import {PetDTO} from "../../../Model/petDTO";
import {AppointmentDTO} from "../../../Model/appointmentDTO";
import {VetsModalComponent} from "../VetsModal/vets-modal.component";
import {PetsModalComponent} from "../../ReusableComponents/PetsModal/pets-modal.component";
import {AppointmentsModalComponent} from "../../ReusableComponents/AppointmentsModal/appointments-modal.component";
import {tap, finalize} from "rxjs";
import { UntilDestroy, untilDestroyed } from '@ngneat/until-destroy';

@UntilDestroy()
@Component({
  selector: 'vets-table',
  templateUrl: './vets-table.component.html',
  styleUrls: ['./vets-table.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class VetsTableComponent implements OnInit{
  vets: Array<VetDTO> = [];
  patients: Array<PetDTO> = [];
  appointments: Array<AppointmentDTO> = [];
  modalAddUpdateRef: MdbModalRef<VetsModalComponent> | null = null;
  modalPatientsRef: MdbModalRef<PetsModalComponent> | null = null;
  modalAppointmentsRef: MdbModalRef<AppointmentsModalComponent> | null = null;
  pageNumber = 1;
  pageSize = 5;
  count = 0;

  constructor(private vetService: VetService, private modalAddUpdateService: MdbModalService,
              private modalPatientsService: MdbModalService, private modalAppointmentsService: MdbModalService) {
  }

  ngOnInit(): void {
    this.getVets();
  }

  handlePageChange(event: any): void {
    this.pageNumber = event;
    this.ngOnInit();
  }

  public getVets(): void {
    this.vetService.getAllPaginatedVets(this.pageNumber, this.pageSize)
      .pipe(
        untilDestroyed(this),
        tap((vets) => {
          this.vets = vets.vets;
          this.count = vets.total;
          this.vets = this.vets.sort((a, b) => a.id - b.id);
        })
      )
      .subscribe(vets => this.vets = vets.vets);
  }

  public addVet(vet: VetDTO): void {
    this.vetService.addVet(vet);
    this.vets.push(vet);
  }

  public deleteVet(id: number): void {
    this.vetService.deleteVet(id);
    this.vets = this.vets.filter((vet) => vet.id != id);
  }

  public updateOwner(vet: VetDTO): void {
    let updatedVet = this.vets.find(function (oldVet) {
      return oldVet.id === vet.id;
    });
    this.vetService.updateVet(vet);
    let index = this.vets.indexOf(updatedVet!);
    this.vets[index] = vet;

  }

  public openModalForAdd(): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(VetsModalComponent, {
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: VetDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.addVet(response);
      }
    });
  }

  public openModalForUpdate(vet: VetDTO): void {
    this.modalAddUpdateRef = this.modalAddUpdateService.open(VetsModalComponent, {
      data: {
        inputId: vet.id,
        inputFirstName: vet.firstName,
        inputLastName: vet.lastName,
        inputEmail: vet.email,
        inputPhoneNumber: vet.phoneNumber,
        inputDateOfBirth: vet.dateOfBirth,
        inputSalary: vet.salary,
        inputRating: vet.rating
      },
      modalClass: 'modal-lg'
    });
    this.modalAddUpdateRef.onClose.subscribe((response: VetDTO | string) => {
      if (typeof response === "string") {
      } else {
        this.updateOwner(response);
      }
    });
  }

  public openAppointmentsModal(id: number): void {
    this.vetService.getVetAppointments(id)
      .subscribe(appointments => {
        this.appointments = appointments.appointments
        this.modalAppointmentsRef = this.modalAppointmentsService.open(AppointmentsModalComponent, {
          data: {
            appointments: this.appointments
          },
          modalClass: 'modal-lg'
        });
      });
  }

  public openPatientsModal(id: number): void {
    this.vetService.getVetPatients(id)
      .subscribe(pets => {
        this.patients = pets.pets
        this.modalPatientsRef = this.modalPatientsService.open(PetsModalComponent, {
          data: {
            pets: this.patients
          },
          modalClass: 'modal-lg'
        });
      });
  }
}
