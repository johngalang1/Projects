def glass(building:list) -> int:  
    """
    Check if there is a 'G' in each column then take the index of the 1st item 
    Store all the indexes into a list and find the sum
    
    """
    glass_amount = 0
    for row in building: 
        for block in row:  
            if block[0] =='G': 
                glass_amount += int(block[1]) 

    return glass_amount

def recycled(building:list) -> int: 
    """
    Check if there exists an 'R' in each column, then store the amount of R's in a variable 
    Use the amount of R's to create the grading score

    """
    recycled_amount = 0 
    recycled_score = 0

    for row in building: 
        for block in row: 
            if block[0] == 'R': 
                recycled_amount += 1

    if recycled_amount == 0:
        recycled_score = 0
    elif recycled_amount == 1:
        recycled_score = 2
    elif recycled_amount == 2:
        recycled_score = 5
    elif recycled_amount == 3:
        recycled_score = 10
    elif recycled_amount == 4:
        recycled_score = 15
    elif recycled_amount == 5:
        recycled_score = 20
    else:
        recycled_score = 30
    
    return recycled_score

def stone(building:list) -> int: 
    """ 
    Find if there exists an 'S' in the sequence of blocks in each row 
    to determine the amount of points
    
    """
    stone_score = 0
    building.reverse() 
    for row in building: 
        for block in row: 
            if row == building[0]:
                if block[0] == 'S':         
                    stone_score += 2 
            elif row == building[1]:
                if block[0] == 'S':         
                    stone_score += 3
            elif row == building[2]:
                if block[0] == 'S':         
                    stone_score += 5 
            elif row == building[3]:
                if block[0] == 'S': 
                    stone_score += 8    
            else: 
                if block[0] == 'S': 
                    stone_score += 8
    return stone_score

def wood(building:list) -> int:
    """ 
    Find if there exists a 'W' in each column of the row 
    Check the indexes beside the block if there exists other blocks, if so give 2 points 
    Check the blocks above or below if the layer exists and if so, 
    Check if there are blocks and give 2 points per block
    
    """
    building.reverse()
    wood_score = 0 
    
    building_index = -1
    for row in building: 
        building_index += 1
        for block in row: 
            if block[0] == 'W':  
                wood_index = row.index(block) 
                #if there is a block on the right
                if ((wood_index + 1) < 3) and row[wood_index + 1] != '--': 
                    wood_score += 2 
                    #if there is a block on the left
                if ((wood_index - 1) >= 0) and row[wood_index - 1]!= '--': 
                        wood_score += 2
                    #if there is block beneath it
                if ((building_index != (len(building) - 1) )) and building[building_index + 1][wood_index] != '--': 
                        wood_score += 2 
                    #if there is a block above it
                if (((building_index + len(building)) != (len(building)))) and building[building_index - 1][wood_index] != '--': 
                        wood_score += 2 
                else: 
                    wood_score += 0


    return wood_score
                                      
def main() -> None:
    file = open(r'./datafiles/building.txt', 'r') # Print out the building
    for lines in file: 
        print(lines.strip('\n')) 
    file.close()

    file = open(r'./datafiles/building.txt', 'r') # Turning the building into a list of lists
    block_list = [] 
    for row in file:
        row = row.strip('\n')
        row = row.split('|')
        block_list.append(row)
    file.close() 
    
    glass_points = glass(block_list)
    recycled_points = recycled(block_list)
    stone_points = stone(block_list)
    wood_points = wood(block_list)
    total = glass_points + recycled_points + stone_points + wood_points
    print(f"+----------+----+\n| glass    |{glass_points:>3} |\n| recycled |{recycled_points:>3} |\n| stone    |{stone_points:>3} |\n| wood     |{wood_points:>3} |\n+==========+====+\n| total    |{total:>3} |\n+----------+----+")
main()
