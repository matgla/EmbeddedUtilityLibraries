((c++-mode (helm-make-build-dir . "bin")))
(setq-default dotspacemacs-configuration-layers
              '((c-c++ :variables
                       c-c++-default-mode-for-headers 'c++-mode'
                       c-c++-enable-clang-support t)))
