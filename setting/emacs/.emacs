;;require plugin:=======================================================
;;;; emacs-goodies-el
;;;; cedet
;;;; ECB
;;;;dedicated

;;load-path=============================================================
(add-to-list 'load-path "~/.emacs.d/site-lisp")

;;custom macro==========================================================
(load-file "~/.emacs.macro")

;;directory=============================================================
;(setq default-directory "~/")

;;abbreviations=========================================================
(setq-default abbrev-mode t)
(read-abbrev-file "~/.abbrev_defs")
(setq save-abbrevs t)

;;;;white space===========================================================
(load-file "~/.emacs.d/site-lisp/whitespace.elc")

;;highlight-char========================================================
(load-file "~/.emacs.d/site-lisp/highlight-chars.elc")
;; (setq whitespace-display-mappings
;;       '((tab-mark   ?\t   [?\xBB ?\t] [?\\ ?\t])
;; ;;	(space-mark   ?\    [?\xB7]     [?.])	; space
;; ;;	(space-mark   ?\xA0 [?\xA4]     [?_])	; hard space
;; ;;	(newline-mark ?\n   [?\xB6 ?\n] [?$ ?\n])	; end-of-line
;; 	))

;;======================================================================
;;Custom function=======================================================
;;======================================================================

;;exit-recursive-edit
(global-set-key "\C-xj" 'exit-recursive-edit)

;;overwrite-mode
(global-set-key "\C-x\C-j" 'overwrite-mode)

;; Maximum frame========================================================
(defun maximize-frame () 
  (interactive)
  (set-frame-position (selected-frame) 0 0)
  (set-frame-size (selected-frame) 1000 1000))

(global-set-key (kbd "<s-return>") 'maximize-frame)

;;time-insert===========================================================
(defun insert-current-date-time ()
  "Insert string for the current time formatted like '2:34 PM'."
  (interactive)                 ; permit invocation in minibuffer
  (insert (format-time-string "%D %-H:%M")))

(defun insert-current-date ()
  "Insert string for today's date nicely formatted in American style,
e.g. Sunday, September 17, 2000."
  (interactive)                 ; permit invocation in minibuffer
  (insert (format-time-string "%D")))

;;Windows frame size====================================================
(global-set-key "\M-]" 'enlarge-window-horizontally)
(global-set-key "\M-[" 'shrink-window-horizontally)
(global-set-key "\M-n" 'enlarge-window)
(global-set-key "\M-p" 'shrink-window)

;;Cua-mode==============================================================
(cua-selection-mode t)
;(global-set-key [f12] 'cua-mode)

;;password invisible====================================================
(add-hook 'comint-output-filter-functions
   'comint-watch-for-password-prompt)

;;compile===============================================================
(global-set-key "\C-ca" 'compile)

;;compression-mode======================================================
(auto-compression-mode)

;;workspace=============================================================
(global-set-key "\C-cwr" 'works-mac-right)
(global-set-key "\C-cwd" 'works-mac-bottom)

;;shell=================================================================
(global-set-key "\C-c\C-t" 'shell)
;(global-set-key "\C-ct" 'newshell)
(setq ansi-color-for-comint-mode t)
;(customize-group 'ansi-colors)

;;completions buffer====================================================
(add-to-list 'special-display-regexps '("*com.*" my-display-completions))
;(add-to-list 'special-display-buffer-names '(".*"))
(defun my-display-completions (buf)
  "put the *completions* buffer in the right spot"
  (let ((windows (delete (minibuffer-window) (window-list))))
    (if (eq 1 (length windows))
        (progn 
          (select-window (car windows))
          (split-window-vertically)))
    (let ((target-window (window-at (- (frame-width) 4) (- (frame-height) 4)))
          (pop-up-windows t))
      (set-window-buffer target-window buf)
      target-window)))

(defun display-buffer-avoiding-lr-corner (buffer &optional not-this-window)
   "Put new open file to frame not in right bottom corner"
;   (if (member (buffer-name buffer) special-display-buffer-names)
;       (my-display-completions buffer)
     (save-selected-window
       (when (buffer-file-name buffer)
 	(select-window (window-at (- (frame-width) 4)
 				  (- (frame-height) 4))))
       (let ((display-buffer-function nil))
	 (display-buffer buffer not-this-window))))

(setq display-buffer-function 'display-buffer-avoiding-lr-corner)


;;comment-region========================================================
(global-set-key "\C-c\C-c" 'comment-region)

;;Jump to other windows=================================================
(global-set-key "\C-cf" 'windmove-right)
(global-set-key "\C-cn" 'windmove-down)
(global-set-key "\C-cp" 'windmove-up)
(global-set-key "\C-cb" 'windmove-left)

;;======================================================================
;;Tools=================================================================
;;======================================================================

;;slime=================================================================
(add-to-list 'load-path "/opt/slime/")  ; your SLIME directory
(setq inferior-lisp-program "/usr/local/bin/sbcl") ; your Lisp system
(require 'slime)
(slime-setup '(slime-repl))
(global-set-key "\C-cl" 'slime)

;;;;indent-complete---------------------------------------------
;; (defun my-indent-or-complete-lisp ()
;;   (if (looking-at "\\>")
;;       (slime-complete-symbol)
;;     (indent-for-tab-command)
;;     )
;;   )

;; (defun my-emacs-slime-mode-hook()
;;   (define-key sldb-hook-map [(tab)] 'my-indent-or-complete-lisp)
;;   )

;; (add-hook 'sldb-hook 'my-emacs-slime-mode-hook)

;;======================================================================
;; For maximum startup speed you can include the Swank server directly 
;; in a core file. The disadvantage of this approach is that the setup 
;; is a bit more involved and that you need to create a new core file 
;; when you want to update SLIME or SBCL. The steps to execute are:
;;    shell$ sbcl
;;    * (load "/opt/slime/swank-loader.lisp")
;;    * (swank-loader:dump-image "sbcl.core-with-swank")
;; mv this core file to /usr/local/lib/sbcl/
(setq slime-lisp-implementations
      '((sbcl ("sbcl" "--core" "/usr/local/lib/sbcl/sbcl.core-with-swank")
	      :init (lambda (port-file _)
		      (format "(swank:start-server %S)\n" port-file)))))


;;scheme=================================================================
(require 'xscheme)
(global-set-key "\C-cs" 'run-scheme)

;;Aspell check==========================================================
(setq ispell-program-name "aspell"
      ispell-dictionary "english"
      ispell-dictionary-alist
      (let ((default '("[A-Za-z]" "[^A-Za-z]" "[']" nil
                       ("-B" "-d" "english" "--dict-dir"
                        "/Library/Application Support/cocoAspell/aspell6-en-6.0-0")
                       nil iso-8859-1)))
        `((nil ,@default)
          ("english" ,@default))))

;;color-theme===========================================================
; (load-file "~/.emacs.d/site-lisp/color-theme.el")
; (require 'color-theme)
; (setq color-theme-is-global t)
; (color-theme-select)
; (color-theme-billw)
; (kill-this-buffer)

;;dedicated-mode========================================================
(load-file "~/.emacs.d/site-lisp/dedicated.elc")
(require 'dedicated)

;;thumbs================================================================
(autoload 'thumbs "thumbs" "Preview images in a directory." t)

;;cedet=================================================================
(defun use-cedet()
  (load-file "~/.emacs.d/site-lisp/cedet-mode.el")
)
;;======================================================================
;;Language mode ========================================================
;;======================================================================


;; CC-model==============================================================
;;;; http://cc-mode.sourceforge.net/
(require 'cc-mode)
(c-set-offset 'inline-open 0)
(c-set-offset 'friend '-)
(c-set-offset 'substatement-open 0)
(load-file "~/.emacs.d/site-lisp/cuda_mode.elc")

(defun my-c-mode-common-hook()
  (setq tab-width 4 indent-tabs-mode nil)
  (define-key c-mode-base-map [(control \`)] 'hs-toggle-hiding)
  (define-key c-mode-base-map "\C-x/" 'c-comment-title)
  (define-key c-mode-base-map "\C-c/" 'c-debug-title)
  (define-key c-mode-base-map [(control ?/)] 'c-comment-date)
  (define-key c-mode-base-map [f12] 'use-cedet)
  (setq c-macro-shrink-window-flag t)
  (setq c-macro-preprocessor "cpp")
  (setq c-macro-cppflags " ")
  (setq c-macro-prompt-flag t)
  (setq hs-minor-mode t)
  (setq abbrev-mode t)
)
(add-hook 'c-mode-common-hook 'my-c-mode-common-hook)
(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))

;;Shell mode============================================================
(defun my-sh-mode-common-hook()
  (define-key sh-mode-map [(control ?/)] 'sh-comment-add)
  )
(add-hook 'sh-mode-hook 'my-sh-mode-common-hook)
 
;;fortran mode==========================================================

(add-hook 'fortran-mode-hook 'hc-highlight-tabs)

(defun my-fortran-mode-common-hook()
  (setq auto-fill-mode t)
  (define-key fortran-mode-map "\C-x/" 'fortran-comment-title)
  (define-key fortran-mode-map [(control ?/)] 'fortran-comment-add)
  )
(add-hook 'fortran-mode-hook 'my-fortran-mode-common-hook)

;;outline mode-=========================================================
(setq default-major-mode 'outline-mode)
(defun my-outline-mode-hook()
  (define-key outline-mode-map "\C-c1" 'outline-title1)
  (define-key outline-mode-map "\C-c2" 'outline-title2)
  (define-key outline-mode-map "\C-c3" 'outline-title3)
  (define-key outline-mode-map "\C-c4" 'outline-title4)
  (define-key outline-mode-map "\C-c5" 'outline-title5)
  (define-key outline-mode-map "\C-c6" 'outline-title6)
  (define-key outline-mode-map "\C-c7" 'outline-title7)
  (define-key outline-mode-map "\C-c8" 'outline-title8)
  (define-key outline-mode-map "\C-c9" 'outline-title9)
)
(add-hook 'outline-mode-hook 'my-outline-mode-hook)
(add-hook 'outline-mode-hook 'hc-highlight-tabs)

;;text mode=============================================================
(setq default-fill-column 80)
(add-to-list 'auto-mode-alist '("\\.txt\\'" . outline-mode))

;;emacs-lisp mode=======================================================
(defun my-emacs-lisp-mode-hook()
  (define-key emacs-lisp-mode-map "\C-x/" 'lisp-comment-add)
  (define-key emacs-lisp-mode-map [(control ?/)] 'lisp-comment-add-sub)
  )
(add-hook 'emacs-lisp-mode-hook 'my-emacs-lisp-mode-hook)

;;Latex-mode============================================================
(defun my-latex-mode-commom-hook()
  (define-key latex-mode-map [(control ?/)] 'latex-comment-line)
  )
(add-hook 'latex-mode-hook 'my-latex-mode-common-hook)
(add-hook 'tex-mode-hook 'my-latex-mode-common-hook)
(add-hook 'LaTeX-mode-hook 'my-latex-mode-common-hook)
(add-hook 'TeX-mode-hook 'my-latex-mode-common-hook)

;;GNUplot-mode==========================================================
;; load the file
(load-file "~/.emacs.d/site-lisp/gnuplot-mode.elc")
;(require 'gnuplot)

;; specify the gnuplot executable (if other than /usr/bin/gnuplot)
(setq gnuplot-program "/usr/local/bin/gnuplot")

;; automatically open files ending with .gp or .gnuplot in gnuplot mode
(setq auto-mode-alist 
(append '(("\\.\\(gp\\|gnuplot\\|plt\\)$" . gnuplot-mode)) auto-mode-alist))

;;======================================================================
;;Options of emacs======================================================
;;======================================================================
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(inhibit-startup-screen t)
 '(size-indication-mode t)
 '(slime-complete-symbol-function (quote slime-simple-complete-symbol))
 '(tool-bar-mode nil))
;;(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
;; '(default ((t (:inherit nil :stipple nil :background "black" :foreground "cornsilk" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 103 :width normal :foundry "unknown" :family "DejaVu Sans Mono")))))

;; end-of-emacs-auto-compile.el
;(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
; '(default ((t (:inherit nil :stipple nil :background "black" :foreground "cornsilk" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 93 :width normal :foundry "unknown" :family "DejaVu Sans Mono")))))

;;======================================================================
;;----------------Unused part-------------------------------------------
;;======================================================================

;;ECB===================================================================
;; (add-to-list 'load-path "~/.emacs.d/site-lisp/ecb-2.40")
;; (load-file "~/.emacs.d/site-lisp/ecb-2.40/ecb.el")
;; (require 'ecb)
;; (setq ecb-auto-activate nil
;;       ecb-tip-of-the-day nil
;;       ecb-tree-indent 4
;;       ecb-windows-height 0.5
;;       ecb-windows-width 0.20)
;; ecb-auto-compatibility-check nil
;; ecb-version-check nil
;; inhibit-startup-message t
;; (global-set-key [f12] 'ecb-activate);;定义F12键为激活ecb
;; (global-set-key [C-f12] 'ecb-deactivate) ;;定义Ctrl+F12为停止ecb
;; (global-set-key "\C-cs" 'ecb-goto-window-sources)
;; (global-set-key "\C-cm" 'ecb-goto-window-methods)
;; (global-set-key "\C-c1" 'ecb-goto-window-edit1)
;; (global-set-key "\C-c2" 'ecb-goto-window-edit2)
;; (global-set-key "\C-cd" 'ecb-goto-window-directories)


;;windows===============================================================
;(global-set-key [(f9)] 'my-fullscreen)

;;Xcscope===============================================================
;(require 'xcscope) ;;xcscope
;(global-set-key "\C-xg" 'cscope-find-global-definition-no-prompting);; find global definition for the current position


;;Latex mode==============================================================
;; (defun my-latex-mode-hook()
;;   (define-key latex-mode-map [(tab)] 'my-indent-or-hippie-expand)
;; )
;; (add-hook 'latex-mode-hook 'my-latex-mode-hook)

;;C++ mode====================================================================
;(defun my-c++-mode-hook()
;  (setq tab-width 4 indent-tabs-mode nil)
;  (c-set-style "stroustrup")
;;  (define-key c++-mode-map [f3] 'replace-regexp)
;  (define-key c++-mode-map "\C-x/" 'c-comment-title)
;  (define-key c++-mode-map [(tab)] 'my-indent-or-complete)
;)

;;task windows================================================================
;(global-set-key "\C-xt" 'task)
;(global-set-key "\C-cc" 'calendar)
;(diary)

;;Maximized frames=========================================================
;; (defun my-maximized ()
;;   (interactive)
;;   (x-send-client-message
;;    nil 0 nil "_NET_WM_STATE" 32
;;    '(2 "_NET_WM_STATE_MAXIMIZED_HORZ" 0))
;;   (interactive)
;;   (x-send-client-message
;;    nil 0 nil "_NET_WM_STATE" 32
;;    '(2 "_NET_WM_STATE_MAXIMIZED_VERT" 0)))

;;(global-set-key [(f9)] 'my-maximized)

;;(run-with-idle-timer 0.1 nil 'my-maximized)

;; (defun my-fullscreen ()
;;          (interactive)
;;          (set-frame-parameter nil 'fullscreen
;;                               (if (frame-parameter nil 'fullscreen) nil 'fullboth)))

;(put 'scroll-left 'disabled nil)

;; completion-ui=====================================================
;(add-to-list 'load-path "~/.emacs.d/site-lisp/completion-ui")
;(require 'completion-ui)

;; Jump to temp
;;(jumptemp)
;(eshell)

;; emacs-auto-compile.el
 
;; Auto compiles .emacs whenever a change is saved.
(defun auto-compile nil
  "recompiles ~/.emacs when any changes happen to it."
  (interactive)
  (require 'bytecomp)
  (if (string= (buffer-file-name)
	       (expand-file-name (concat default-directory ".emacs")))
      (byte-compile-file (buffer-file-name))))
(add-hook 'after-save-hook 'auto-compile)
 
;(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
; '(default ((t (:inherit nil :stipple nil :background "black" :foreground "cornsilk" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 97 :width normal :foundry "unknown" :family "DejaVu Sans Mono")))))
