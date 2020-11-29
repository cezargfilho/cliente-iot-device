package client;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;

import com.google.gson.Gson;

public class Cliente {

	private static List<String> temperaturas = new ArrayList<>();
	private static List<String> umidades = new ArrayList<>();
	private static List<String> radiacoes = new ArrayList<>();
	private static List<String> irrigacoes = new ArrayList<>();
	static final String SECRET_KEY = "etmtNSgn";

	public static void main(String[] args) throws FileNotFoundException {

		Scanner sc = new Scanner(new File("input.txt"));
		try {

			while (sc.hasNextLine()) {
				String linha = sc.nextLine();
				String[] strings = linha.split("\\s+");

				if (linha.equalsIgnoreCase(" ") || linha == null) {
					System.out.println("\nCHAVE-> " + strings[0]);
					System.out.println("VALOR-> " + strings[1]);
				}

				if (strings[0].equalsIgnoreCase("TEMPERATURA")) {
					String val = AES.encrypt(strings[1], SECRET_KEY);
					temperaturas.add(val);
				} else if (strings[0].equalsIgnoreCase("UMIDADE")) {
					String val = AES.encrypt(strings[1], SECRET_KEY);
					umidades.add(val);
				} else if (strings[0].equalsIgnoreCase("RADIACAO")) {
					String val = AES.encrypt(strings[1], SECRET_KEY);
					radiacoes.add(val);
				} else if (strings[0].equalsIgnoreCase("IRRIGACAO")) {
					String val = AES.encrypt(strings[1], SECRET_KEY);
					irrigacoes.add(val);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			sc.close();
		}

		doPost(umidades, temperaturas, radiacoes, irrigacoes);
		sc.close();
	}

	private static void doPost(List<String> umid, List<String> temp, List<String> rad, List<String> irr) {
		List<Json> listJson = new ArrayList<>();

		for (int i = 0; i < umid.size(); i++) {
			Json json = new Json();
			json.setUmidade(umid.get(i));
			json.setTemperatura(temp.get(i));
			json.setRadiacaoSolar(rad.get(i));
			json.setTempoIrrigacao(irr.get(i));
			listJson.add(json);
		}

		CloseableHttpClient client = HttpClients.createDefault();
		HttpPost httpPost = new HttpPost("https://murmuring-shore-83165.herokuapp.com/dados/create/list");

		Gson gson = new Gson();
		String jsonString = gson.toJson(listJson);
		System.out.println(jsonString);

		StringEntity entity;
		try {
			entity = new StringEntity(jsonString);

			httpPost.setEntity(entity);
			httpPost.setHeader("key", SECRET_KEY);
			httpPost.setHeader("Accept", "application/json");
			httpPost.setHeader("Content-type", "application/json");

			CloseableHttpResponse response = client.execute(httpPost);
			int statusCode = response.getStatusLine().getStatusCode();
			System.out.println("RESPOSTA= " + statusCode);
		} catch (IOException e) {

			e.printStackTrace();
		} finally {
			try {
				client.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

}