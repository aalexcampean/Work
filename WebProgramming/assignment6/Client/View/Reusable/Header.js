const headerTemplate = document.createElement('template');

headerTemplate.innerHTML = `
  <style>
    * {
        padding: 0;
        margin: 0;
    }
    
    header {
        height: 40px;
        padding: 20px 20px 150px 20px;
        
        font-family: "Acari Sans";
        
        display: flex;
        align-items: center;
        justify-content: space-between;
    }
    
    .page-title {
        color: #0101fc;
        font-size: 20pt;
    }
    
    #menu {
        display: flex;
        align-items: center;
        justify-content: center;
    }

    ul li {
        list-style: none;
        display: inline;
    }
    
    a {
        text-decoration: none;
        font-size: 14pt;
    }
    
    .navigation-link {
        font-weight: 700;
        margin: 0 25px;
        color: #99a5f9;
    }
    
    .navigation-link:hover {
        padding-bottom: 5px;
        color: #0101fc;
    }
  </style>
  <header>
    <div>
        <a class="page-title" href="LandingPage.php">
            <h1>Easy Manager</h1>
        </a>
    </div>
    <nav>
      <ul id="menu">
        <li><a class="navigation-link" href="LandingPage.php">Home</a></li>
        <li><a class="navigation-link" href="DocumentManager.php">Manage Documents</a></li>
      </ul>
    </nav>
  </header>
`;

class Header extends HTMLElement {
    constructor() {
        super();
    }

    connectedCallback() {
        const shadowRoot = this.attachShadow({mode: 'open'});

        shadowRoot.appendChild(headerTemplate.content);
    }
}

customElements.define('custom-header', Header);