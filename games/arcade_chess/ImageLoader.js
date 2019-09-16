let images = {
  b_pawn: null,
  b_rook: null,
  b_knight: null,
  b_bishop: null,
  b_king: null,
  b_queen: null,
  w_pawn: null,
  w_rook: null,
  w_knight: null,
  w_bishop: null,
  w_king: null,
  w_queen: null,
}

let imagesLeftToLoad = 0

function handleImageLoaded() {
  imagesLeftToLoad--
  if(imagesLeftToLoad <= 0) {
    startEngine()
  }
}

function startEngine() {

}


export const loadImages = (cb) => {
  let image_files = [
      'b_pawn.png', 'b_rook.png', 'b_knight.png', 'b_bishop.png', 'b_king.png', 'b_queen.png',
      'w_pawn.png', 'w_rook.png', 'w_knight.png', 'w_bishop.png', 'w_king.png', 'w_queen.png',
  ]

  imagesLeftToLoad = image_files.length

  for(let key in images) {
    images[key] = document.createElement('img')
    images[key].onload = handleImageLoaded
    images[key].src = `images/${key}.png`
  }

  startEngine = cb
}

export default images