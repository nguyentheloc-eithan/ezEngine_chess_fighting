   for (int i = 0; i < num_walls; i++)
    {
        outputFile << "( " << arr_walls[i][0] << "," << arr_walls[i][1] << ")"
                   << " ";
    }
    outputFile << "\nnum_fake_walls : " << num_fake_walls << endl;
    for (int i = 0; i < num_fake_walls; i++)
    {
        outputFile << "( " << arr_fake_walls[i][0] << "," << arr_fake_walls[i][1] << ")"
                   << " ";
    }