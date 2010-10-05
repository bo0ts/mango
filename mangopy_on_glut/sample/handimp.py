import handlib

oh = handlib.OscillatingHand()
oh.position = (4, 0, 0)
oh.set(RENDER | STEP)

bh = handlib.BringItOnHand()
bh.set(RENDER | STEP)
