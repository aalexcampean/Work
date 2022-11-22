import {Component, Input, OnInit} from '@angular/core';
import {MdbModalRef} from 'mdb-angular-ui-kit/modal';
import {ProjectDTO} from "../../Model/projectDTO";

@Component({
    selector: 'projects-modal',
    templateUrl: './projects-modal.component.html',
    styleUrls: ['./projects-modal.component.css']
})
export class ProjectsModalComponent {
    inputMemberName: string | null = null;
    inputProjectNames: string | null = null;

    constructor(public modalRef: MdbModalRef<ProjectsModalComponent>) {
    }

    close(): void {
        this.modalRef.close("Modal was closed");
    }

    submitInformation(): void {
        const projectNames = this.inputProjectNames!.split(',')
        if (projectNames == []) return;
        this.modalRef.close({
            memberName: this.inputMemberName,
            projects: projectNames
        });
    }
}
