struct Request{
    int machine; // El ID de la maquina a entregar
    int amount;

    // Constructor
    Request(int id, int _amount){
        machine = id;
        amount = _amount;
    }
};
