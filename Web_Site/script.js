/* script.js — common script for all pages */

// ---------- Helper & DOM shortcuts ----------
const $ = (sel, ctx=document) => ctx.querySelector(sel);
const $$ = (sel, ctx=document) => Array.from((ctx || document).querySelectorAll(sel));
const on = (el, ev, fn) => { if(!el) return; el.addEventListener(ev, fn); };

// ---------- Responsive hamburger (mobile nav) ----------
(() => {
  const hamburger = $('.hamburger');
  const navLinks = $('.nav-links');
  if(!hamburger) return;
  hamburger.addEventListener('click', () => {
    navLinks.style.display = (getComputedStyle(navLinks).display === 'flex') ? 'none' : 'flex';
  });
})();

// ---------- Gallery: 1s auto, arrows, dots, hover pause, keyboard ----------
(() => {
  const slides = $$('.slide');
  if(!slides.length) return;
  const prevArrow = $('.arrow.prev');
  const nextArrow = $('.arrow.next');
  const dotsContainer = $('.dots');
  let index = 0;
  const INTERVAL = 1000; // 1s
  let timer = null;

  // build dots
  slides.forEach((_, i) => {
    const dot = document.createElement('button');
    dot.className = (i===0)?'dot active':'dot';
    if(dotsContainer) dotsContainer.appendChild(dot);
    dot.addEventListener('click', () => { stop(); show(i); start(); });
  });
  const dots = $$('.dot');

  function show(i){
    index = (i + slides.length) % slides.length;
    slides.forEach((s, j) => s.classList.toggle('active', j===index));
    dots.forEach((d, j) => d.classList.toggle('active', j===index));
  }

  function nextSlide(){ show(index+1); }
  function prevSlide(){ show(index-1); }

  on(nextArrow, 'click', ()=>{ stop(); nextSlide(); start(); });
  on(prevArrow, 'click', ()=>{ stop(); prevSlide(); start(); });

  // keyboard navigation
  document.addEventListener('keydown', (e) => {
    if(e.key === 'ArrowRight'){ stop(); nextSlide(); start(); }
    if(e.key === 'ArrowLeft'){ stop(); prevSlide(); start(); }
  });

  function start(){ stop(); timer = setInterval(nextSlide, INTERVAL); }
  function stop(){ if(timer){ clearInterval(timer); timer = null; } }

  // pause on hover
  const gallery = document.querySelector('.gallery');
  if(gallery){
    gallery.addEventListener('mouseenter', stop);
    gallery.addEventListener('mouseleave', start);
  }

  // init
  show(0);
  start();
})();

// ---------- Storage helpers ----------
const STORAGE_KEY = 'sophia_models_v1';
const loadModels = () => {
  try { 
    const raw = localStorage.getItem(STORAGE_KEY); 
    return raw ? JSON.parse(raw) : DEFAULTS; 
  }
  catch(e){ 
    console.warn('load models error', e); 
    return DEFAULTS; 
  }
};
const saveModels = (arr) => { localStorage.setItem(STORAGE_KEY, JSON.stringify(arr)); };

// ---------- Render models ----------
let models = loadModels();
function renderModels(){
  container.innerHTML = '';
  models.forEach(model=>{
    const card = document.createElement('div'); 
    card.className = 'model-card';
    card.dataset.id = model.id;
    card.innerHTML = `
      <h2>${escapeHtml(model.title)}</h2>
      <p class="model-meta">${escapeHtml(model.desc)}</p>
      <div class="model-actions">
        <button class="btn white edit">Edit</button>
        <button class="btn outline clone">Clone</button>
      </div>`;
    container.appendChild(card);

    // events
    card.querySelector('.edit').addEventListener('click', ()=> openEditor(model.id));
    card.querySelector('.clone').addEventListener('click', ()=> { 
      const copy = { ...model, id: generateId(), title: model.title + ' (Copy)' }; 
      models.push(copy); 
      saveModels(models); 
      renderModels();
    });
  });
}

// ---------- Editor bindings ----------
const inputTitle = $('#mTitle');
const inputDesc = $('#mDesc');
const inputNotes = $('#mNotes');
const saveBtn = $('#saveModelBtn');
const deleteBtn = $('#deleteModelBtn');
let editingId = null;

function openEditor(id){
  const model = models.find(x=>x.id===id);
  if(!model) return;
  editingId = id;
  inputTitle.value = model.title || '';
  inputDesc.value = model.desc || '';
  inputNotes.value = model.notes || '';
  Modal.open();
}



// ---------- Small utilities ----------
function generateId(){ return 'm_' + Math.random().toString(36).slice(2,9); }
function escapeHtml(text){ 
  return text.replaceAll?.('&','&amp;').replaceAll?.('<','&lt;').replaceAll?.('>','&gt;') || (''+text); 
}
