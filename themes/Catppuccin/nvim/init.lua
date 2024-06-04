require('core.options')
require('core.plugins')
require('core.mappings')
-- Plugin configs
require('core.configs.lsp')
require('core.configs.nvim-cmp')
require('core.configs.toggle-term')
require('core.configs.dressing')
require('core.configs.notify')
require("core.configs.fine-cmdline")
require("mason").setup()

-- Color Scheme
vim.cmd('colorscheme catppuccin-mocha')

-- Airline Theme
vim.g.airline_theme = 'catppuccin'
vim.g.airline_powerline_fonts = 1

-- Transparent bg
-- vim.api.nvim_set_hl(0, "Normal", { bg = "none" })
-- vim.api.nvim_set_hl(0, "float", { bg = "none" })

-- Optimize loading lua modules and startup time
vim.loader.enable()
