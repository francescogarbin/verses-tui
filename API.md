# TODO: translate this s*t in english

# Verses API Reference

Documentazione delle API REST per l'applicazione di note-taking Verses.

## Base URL

```
http://localhost:8000
```

In produzione con Nginx, le API sono esposte sotto `/api/*`.

## Autenticazione

Le API protette richiedono un token JWT nell'header `Authorization`:

```
Authorization: Bearer <access_token>
```

Il token si ottiene tramite l'endpoint `/login`.

---

## Endpoints

### Health & Info

#### `GET /`
Endpoint root, informazioni sul servizio.

**Risposta:**
```json
{
  "message": "Welcome to Verses API",
  "version": "1.0.0",
  "status": "running",
  "docs": "/docs"
}
```

#### `GET /health`
Health check.

**Risposta:**
```json
{
  "status": "healthy"
}
```

---

### Autenticazione

#### `POST /register`
Registra un nuovo utente. Crea automaticamente un notebook di default.

**Request Body:**
```json
{
  "email": "user@example.com",
  "username": "username",
  "password": "password123"
}
```

**Risposta (201 Created):**
```json
{
  "id": 1,
  "email": "user@example.com",
  "username": "username",
  "created_at": "2025-01-15T10:30:00"
}
```

**Errori:**
- `400 Bad Request` - Email o username già registrati

---

#### `POST /login`
Autentica l'utente e restituisce un token JWT.

**Request Body:**
```json
{
  "username": "username",
  "password": "password123"
}
```

**Risposta (200 OK):**
```json
{
  "access_token": "eyJhbGciOiJIUzI1NiIs...",
  "token_type": "bearer"
}
```

**Errori:**
- `401 Unauthorized` - Credenziali non valide

---

#### `GET /me`
Restituisce le informazioni dell'utente autenticato.

**Richiede:** Autenticazione

**Risposta (200 OK):**
```json
{
  "id": 1,
  "email": "user@example.com",
  "username": "username",
  "created_at": "2025-01-15T10:30:00"
}
```

---

### Notebooks

#### `GET /notebooks`
Lista tutti i notebook dell'utente, ordinati per data di creazione (ascendente).

**Richiede:** Autenticazione

**Risposta (200 OK):**
```json
[
  {
    "id": 1,
    "name": "Notebook",
    "color": "#8B5A3C",
    "created_at": "2025-01-15T10:30:00",
    "updated_at": "2025-01-15T10:30:00"
  }
]
```

---

#### `GET /notebooks/{notebook_id}`
Ottiene un notebook specifico.

**Richiede:** Autenticazione

**Parametri URL:**
- `notebook_id` (int) - ID del notebook

**Risposta (200 OK):**
```json
{
  "id": 1,
  "name": "Notebook",
  "color": "#8B5A3C",
  "created_at": "2025-01-15T10:30:00",
  "updated_at": "2025-01-15T10:30:00"
}
```

**Errori:**
- `404 Not Found` - Notebook non trovato o non appartiene all'utente

---

#### `POST /notebooks`
Crea un nuovo notebook.

**Richiede:** Autenticazione

**Request Body:**
```json
{
  "name": "My Notebook",
  "color": "#3498db"
}
```

| Campo | Tipo | Default | Descrizione |
|-------|------|---------|-------------|
| name | string | "Notebook" | Nome del notebook |
| color | string | "#8B5A3C" | Colore in formato hex |

**Risposta (201 Created):**
```json
{
  "id": 2,
  "name": "My Notebook",
  "color": "#3498db",
  "created_at": "2025-01-15T11:00:00",
  "updated_at": "2025-01-15T11:00:00"
}
```

---

#### `PUT /notebooks/{notebook_id}`
Aggiorna nome e/o colore di un notebook.

**Richiede:** Autenticazione

**Parametri URL:**
- `notebook_id` (int) - ID del notebook

**Request Body:**
```json
{
  "name": "New Name",
  "color": "#e74c3c"
}
```

Tutti i campi sono opzionali.

**Risposta (200 OK):**
```json
{
  "id": 1,
  "name": "New Name",
  "color": "#e74c3c",
  "created_at": "2025-01-15T10:30:00",
  "updated_at": "2025-01-15T12:00:00"
}
```

**Errori:**
- `404 Not Found` - Notebook non trovato

---

#### `DELETE /notebooks/{notebook_id}`
Elimina un notebook e tutte le sue note (cascade delete).

**Richiede:** Autenticazione

**Parametri URL:**
- `notebook_id` (int) - ID del notebook

**Risposta:** `204 No Content`

**Errori:**
- `400 Bad Request` - Non puoi eliminare l'ultimo notebook
- `404 Not Found` - Notebook non trovato

---

### Notes

#### `GET /notebooks/{notebook_id}/notes`
Lista tutte le note in un notebook, ordinate per `updated_at` (decrescente, più recenti prima).

**Richiede:** Autenticazione

**Parametri URL:**
- `notebook_id` (int) - ID del notebook

**Risposta (200 OK):**
```json
[
  {
    "id": 1,
    "title": "Prima riga della nota...",
    "content": "Prima riga della nota\n\nContenuto completo...",
    "created_at": "2025-01-15T10:30:00",
    "updated_at": "2025-01-15T14:00:00",
    "notebook_id": 1
  }
]
```

**Note:**
- Il campo `title` è derivato automaticamente dai primi 50 caratteri della prima riga del contenuto
- Se la prima riga è vuota o il contenuto è vuoto, il titolo sarà "Untitled"
- Se il titolo supera 50 caratteri, viene troncato con "..."

**Errori:**
- `404 Not Found` - Notebook non trovato

---

#### `GET /notes/{note_id}`
Ottiene una nota specifica.

**Richiede:** Autenticazione

**Parametri URL:**
- `note_id` (int) - ID della nota

**Risposta (200 OK):**
```json
{
  "id": 1,
  "title": "Prima riga della nota...",
  "content": "Prima riga della nota\n\nContenuto completo...",
  "created_at": "2025-01-15T10:30:00",
  "updated_at": "2025-01-15T14:00:00",
  "notebook_id": 1
}
```

**Errori:**
- `404 Not Found` - Nota non trovata

---

#### `POST /notes`
Crea una nuova nota in un notebook.

**Richiede:** Autenticazione

**Request Body:**
```json
{
  "content": "Contenuto della nota",
  "notebook_id": 1
}
```

| Campo | Tipo | Default | Richiesto | Descrizione |
|-------|------|---------|-----------|-------------|
| content | string | "" | No | Contenuto della nota |
| notebook_id | int | - | **Sì** | ID del notebook di destinazione |

**Risposta (201 Created):**
```json
{
  "id": 2,
  "title": "Contenuto della nota",
  "content": "Contenuto della nota",
  "created_at": "2025-01-15T15:00:00",
  "updated_at": "2025-01-15T15:00:00",
  "notebook_id": 1
}
```

**Errori:**
- `404 Not Found` - Notebook non trovato

---

#### `PUT /notes/{note_id}`
Aggiorna una nota esistente.

**Richiede:** Autenticazione

**Parametri URL:**
- `note_id` (int) - ID della nota

**Request Body:**
```json
{
  "content": "Nuovo contenuto",
  "notebook_id": 2
}
```

Tutti i campi sono opzionali. Specificare `notebook_id` per spostare la nota in un altro notebook.

**Risposta (200 OK):**
```json
{
  "id": 1,
  "title": "Nuovo contenuto",
  "content": "Nuovo contenuto",
  "created_at": "2025-01-15T10:30:00",
  "updated_at": "2025-01-15T16:00:00",
  "notebook_id": 2
}
```

**Errori:**
- `404 Not Found` - Nota non trovata o notebook di destinazione non trovato

---

#### `DELETE /notes/{note_id}`
Elimina una nota.

**Richiede:** Autenticazione

**Parametri URL:**
- `note_id` (int) - ID della nota

**Risposta:** `204 No Content`

**Errori:**
- `404 Not Found` - Nota non trovata

---

## Modelli

### User
```
id: int
email: string (unique)
username: string (unique, max 100 chars)
created_at: datetime
```

### Notebook
```
id: int
name: string (max 255 chars)
color: string (hex, 7 chars, es. "#8B5A3C")
created_at: datetime
updated_at: datetime
```

### Note
```
id: int
title: string (derivato, primi 50 chars della prima riga)
content: string (testo completo)
created_at: datetime
updated_at: datetime
notebook_id: int
```

---

## Codici di Errore

| Codice | Significato |
|--------|-------------|
| 200 | OK |
| 201 | Created |
| 204 | No Content (successo senza body) |
| 400 | Bad Request (validazione fallita, ultimo notebook) |
| 401 | Unauthorized (token mancante/invalido) |
| 404 | Not Found (risorsa non trovata o non autorizzata) |

---

## Note per l'implementazione TUI

1. **Flusso di autenticazione:** Salva il token JWT localmente (es. file config) dopo il login
2. **Gestione sessione:** Il token ha una scadenza configurabile lato server (default probabilmente 30-60 min). Gestisci il 401 con re-login
3. **Titoli note:** Sono calcolati server-side dalla prima riga del contenuto, non serve calcolarli client-side
4. **Ordinamento:** Le note sono già ordinate per ultima modifica (più recenti prima), i notebook per data creazione
5. **Constraint importante:** L'utente deve sempre avere almeno un notebook (DELETE fallisce sull'ultimo)
6. **Spostamento note:** Per spostare una nota, usa PUT con il nuovo `notebook_id`
