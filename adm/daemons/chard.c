// chard.c
#pragma optimize
#pragma save_binary

#define HUMAN_RACE "/adm/daemons/race/human"
#define BEAST_RACE "/adm/daemons/race/beast"
#define MONSTER_RACE "/adm/daemons/race/monster"
 
void create() { seteuid(getuid()); }
 
void setup_char(object ob)
{
	string race;
	mapping my;
 
	if (! stringp(race = ob->query("race")))
	{
		race = "����";
		ob->set("race", "����");
	}

	my = ob->query_entire_dbase();

	switch(race)
	{
	case "����":
		HUMAN_RACE->setup_human(ob);
		break;	
	case "��ħ":
		MONSTER_RACE->setup_monster(ob);
		break;	
	case "Ұ��":
		BEAST_RACE->setup_beast(ob);
		break;	
	default: 
		error("Chard: undefined race " + race + ".\n");
	}
 
	if (undefinedp(my["jing"]))
		my["jing"] = my["max_jing"];
	if (undefinedp(my["qi"]))
		my["qi"] = my["max_qi"];
 
	if (undefinedp(my["eff_jing"]) || my["eff_jing"] > my["max_jing"])
		my["eff_jing"] = my["max_jing"];
	if (undefinedp(my["eff_qi"]) || my["eff_qi"] > (my["max_qi"]+ob->query_gain_qi()))
		my["eff_qi"] = my["max_qi"]+ob->query_gain_qi();
 
	if (undefinedp(my["shen_type"])) my["shen_type"] = 0;
 
	if (undefinedp(my["shen"]))
	{
		if (userp(ob))	
			my["shen"] = 0;
		else
			my["shen"] = my["shen_type"] * my["combat_exp"] / 10;
	}
 
	if (! ob->query_max_encumbrance())
		ob->set_max_encumbrance(20000 + ob->query("str") * 2000 + ob->query_str() * 300);
 
	ob->reset_action();
	ob->update_killer();
}
 
varargs object make_corpse(object victim, object killer)
{
	int i;
	object corpse, *inv;
/*
	if (victim->is_ghost())
	{
		inv = all_inventory(victim);
		inv->owner_is_killed(killer);
		inv -= ({ 0 });
		i = sizeof(inv);
		while(i--)
		{
			if(inv[i]->query("owner_id")||inv[i]->query("owner")) continue;
			inv[i]->move(environment(victim));
		}
		return 0;
	}
*/
//	if( base_name(victim)!="/clone/user/user" ) return 0;

	corpse = new(CORPSE_OB);
	corpse->make_corpse(victim, killer);
	return corpse;
}
