// beast.c

#include <race/beast.h>

mapping combat_action =
([
	"hoof": ([
		"action":		"$N�ú�����$n��$l����һ��",
		"damage":		100,
		"damage_type":	"����",
	]),
	"sting": ([
		"action":		"$N��ת����β�ͼ��׼$n��$lһ��",
		"damage":		20,
		"damage_type":	"ҧ��",
	]),
	"bite": ([
		"action":		"$N������������$n��$l�ݺݵ�һҧ",
		"damage":		20,
		"damage_type":	"ҧ��",
	]),
	"claw": ([
		"action":		"$N��צ����$n��$lһץ",
		"damage_type":	"ץ��",
	]),
	"poke": ([
		"action":		"$N������$n��$lһ��",
		"damage":		30,
		"damage_type":	"����",
	]),
	"knock": ([
		"action":		"$Ņ��������$n��$lһ��",
		"damage":		100,
		"damage_type":	"����",
	]),
]);

void create()
{
	seteuid(getuid());
}

void setup_beast(object ob)
{
	mapping my;

	my = ob->query_entire_dbase();

	my["unit"] = "ֻ";

	if (pointerp(my["verbs"]))
		ob->set_default_action(__FILE__, "query_action");
	else
		ob->set_default_action(([ "action" : "$N����$n��%l\n" ]));
	
	if (undefinedp(my["gender"])) my["gender"] = "����";
	if (undefinedp(my["age"])) my["age"] = random(40) + 5;

	if (undefinedp(my["str"])) my["str"] = random(41) + 5;
	if (undefinedp(my["int"])) my["int"] = random(11) + 5;
	if (undefinedp(my["per"])) my["per"] = random(31) + 5;
	if (undefinedp(my["con"])) my["con"] = random(41) + 5;
	if (undefinedp(my["dex"])) my["dex"] = random(41) + 5;

	if (undefinedp(my["max_jing"]))
	{
		if (my["age"] <= 3) my["max_jing"] = 50;
		else if (my["age"] <= 10) my["max_jing"] = 50 + (my["age"] - 3) * 20;
		else if (my["age"] <= 30) my["max_jing"] = 190 + (my["age"] - 10) * 5;
		else my["max_jing"] = my["max_jing"] = 290 + (my["age"] - 30);
	}
	if (undefinedp(my["max_qi"]))
	{
		if (my["age"] <= 5) my["max_qi"] = 50;
		else if (my["age"] <= 20) my["max_qi"] = 50 + (my["age"] - 5) * 25;
		else my["max_qi"] = my["max_qi"] = 425 + (my["age"] - 20) * 5;
	}
	if (! ob->query_weight())
		ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
	string *act;

	act = me->query("verbs");
	return combat_action[act[random(sizeof(act))]];
}
