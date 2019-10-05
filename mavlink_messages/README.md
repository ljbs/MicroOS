1. Modify `.xml` files to your liking
2. Install mavlink according to website
3. Run `python -m mavgenerate`
  - Settings `C`, mavlink version `2.0`
  - Export `microos_messages.xml` and `robot_messages.xml` to one and the same temporary folder
4. Replace files in `Arduino/libraries/microOS/mavlink/` with generated files/folders
