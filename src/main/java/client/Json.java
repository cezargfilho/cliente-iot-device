package client;

public class Json {
	private String umidade;
	private String temperatura;
	private String radiacaoSolar;
	private String tempoIrrigacao;

	public Json() {
	}

	public Json(String umidade, String temperatura, String radiacaoSolar, String tempoIrrigacao) {
		this.umidade = umidade;
		this.temperatura = temperatura;
		this.radiacaoSolar = radiacaoSolar;
		this.tempoIrrigacao = tempoIrrigacao;

	}

	public void setUmidade(String umidade) {
		this.umidade = umidade;
	}

	public void setTemperatura(String temperatura) {
		this.temperatura = temperatura;
	}

	public void setRadiacaoSolar(String radiacaoSolar) {
		this.radiacaoSolar = radiacaoSolar;
	}

	public void setTempoIrrigacao(String tempoIrrigacao) {
		this.tempoIrrigacao = tempoIrrigacao;
	}

}