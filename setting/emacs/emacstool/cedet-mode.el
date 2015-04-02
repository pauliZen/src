;;cedet=================================================================
(load-file "~/.emacs.d/site-lisp/cedet-1.1/common/cedet.el")
(semantic-load-enable-minimum-features)
(semantic-load-enable-code-helpers)
;(semantic-load-enable-guady-code-helpers)
;(semantic-load-enable-excessive-code-helpers)
;(semantic-load-enable-semantic-debugging-helpers)

;;;;C/C++ include path------------------------------------------
(defconst cedet-user-include-dirs
  (list "."
	".."
	"../.."
	"../include"
	"/opt/root/include"
	"~/include"
	"/usr/include/sys"
	"/usr/include/bits"))
(require 'semantic-c nil 'noerror)
(let ((include-dirs cedet-user-include-dirs))
  (mapc (lambda (dir)
	  (semantic-add-system-include dir 'c++-mode)
	  (semantic-add-system-include dir 'c-mode))
	include-dirs))

;;;; code tag folding-------------------------------------------
(require 'semantic-tag-folding nil 'noerror)
(global-semantic-tag-folding-mode 1)
;;;; key defination---------------------------------------------
(global-set-key (kbd "C-?") 'global-semantic-tag-folding-mode)
(define-key semantic-tag-folding-mode-map (kbd "C-c -") 'semantic-tag-folding-fold-block)
(define-key semantic-tag-folding-mode-map (kbd "C-c =") 'semantic-tag-folding-show-block)
(define-key semantic-tag-folding-mode-map (kbd "C--") 'semantic-tag-folding-fold-all)
(define-key semantic-tag-folding-mode-map (kbd "C-=") 'semantic-tag-folding-show-all)

;;;;code jump return--------------------------------------------
(global-set-key "\C-cjb"
		(lambda ()
		  (interactive)
		  (if (ring-empty-p (oref semantic-mru-bookmark-ring ring))
		      (error "Semantic Bookmark ring is currently empty"))
		  (let* ((ring (oref semantic-mru-bookmark-ring ring))
			 (alist (semantic-mrub-ring-to-assoc-list ring))
			 (first (cdr (car alist))))
		    (if (semantic-equivalent-tag-p (oref first tag)
						   (semantic-current-tag))
			(setq first (cdr (car (cdr alist)))))
		    (semantic-mrub-switch-tags first))))

;;;;indent-complete---------------------------------------------
(defun my-indent-or-complete (point)
  (interactive "d")
  (require 'imenu)
  (if (looking-at "\\>")
      (semantic-ia-complete-symbol-menu (point))
    (if (looking-at "\\.\\|>")
	(progn
	  (forward-char 1)
	  (semantic-ia-complete-symbol-menu (point))
	  )
      (indent-for-tab-command))
    )
  )

;; cedet hook for cc-model-------------------------------------
(defun cedet-c-mode-common-hook()
  (define-key c-mode-base-map [(tab)] 'my-indent-or-complete)
  (define-key c-mode-base-map [(control tab)] 'semantic-ia-complete-symbol-menu)
  (define-key c-mode-base-map "\C-cjj" 'semantic-ia-fast-jump)
  )
(add-hook 'c-mod-common-hook 'cedet-c-mode-common-hook)
;; (defun my-indent-or-hippie-expand
;;   (if (looking-at "{")
;;       (hippie-expand)
;;     (indent-for-tab-command)))

;;cedet=================================================================
;      (autoload 'speedbar-frame-mode "speedbar" "Popup a speedbar frame" t)
;      (autoload 'speedbar-get-focus "speedbar" "Jump to speedbar frame" t)
;      (define-key-after (lookup-key global-map [menu-bar tools])
;                 [speedbar]
;                 '("Speedbar" .
;                 speedbar-frame-mode)
;                 [calendar])
;(global-set-key [(f5)] 'speedbar)

;; (setq semanticdb-search-system-databases t)
;; (add-hook 'c-mode-common-hook
;; 	  (lambda ()
;; 	    (setq semanticdb-project-system-databases
;; 		  (list (semanticdb-create-database
;; 			 semanticdb-new-database-class
;; 			 "/usr/include")))))

;(require 'cedet)
;(require 'semantic-ia)
;(require 'semantic-gcc)
;(setq-mode-local c-mode semanticdb-find-default-throttle
;         '(project unloaded system recursive))
;(require 'semanticdb)

;; project root path
;(setq semanticdb-project-roots 
;	  (list
;        (expand-file-name "/")))

;(autoload 'senator-try-expand-semantic "senator")

;(setq hippie-expand-try-functions-list
;	  '(
;		senator-try-expand-semantic
;		try-expand-dabbrev
;		try-expand-dabbrev-visible
;		try-expand-dabbrev-all-buffers
;		try-expand-dabbrev-from-kill
;		try-expand-list
;		try-expand-list-all-buffers
;		try-expand-line
;        try-expand-line-all-buffers
;        try-complete-file-name-partially
;        try-complete-file-name
;	try-expand-whole-kill
;       )
;)

;(global-set-key [(tab)] 'indent-for-tab-command)
;(global-set-key "\M-/" 'hippie-expand)
;(global-set-key "" 'semantic-ia-complete-symbol-menu);;右Ctrl+\ 自动补全menu
