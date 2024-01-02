/** @type {import('tailwindcss').Config} */
module.exports = {
  content: ["./app.html","./assets/**/*.{html,js}"],
  theme: {
    extend: {
      colors: {
        primary: "#000000",
        secondary: "#5AFE73",
        white: "#FFFFFF"
      }
    },
    spacing: {
      '1': '8px',
      '2': '12px',
      '3': '16px',
      '4': '24px',
      '5': '32px',
      '6': '48px',
    }
  },
  plugins: [
    require('@tailwindcss/typography'),
  ],  
  safelist: [
    'flex',
    'flex-col',
  ]
}