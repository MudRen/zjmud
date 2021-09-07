// chuanfu.c ����

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({ "chuan fu", "fu" }));
	set("gender", "����");
	set("age", 36);
	set("long",
	"����һ���ɻ����ϵĴ��򡣱�����˪������͸�������˵ĺ�ˬ��\n"
	);

	set("combat_exp", 10000);
	set("shen_type", 1);

	set("eff_qi",800);
	set("qi",800);
	set("max_neili", 100);
	set("neili", 100);
	set("jiali", 10);
	set("no_zhenjiu", 1);

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
	object myenv;
	object *obs;

	if (ob->query("money_id") && ob->value() >= 100)
	{
		message_vision("�����$N˵���ã���Ȼ��λ" + RANK_D->query_respect(who) +
			       "Ҫ������\n���Ҿ��������������ɣ�\n" , who);
		message_vision("�����ô�����˴���һ������ê�������ŷ��밶��......\n", who);
		obs = all_inventory(environment());
		obs = filter_array(obs, (: $1 == $(who) || $1->is_character() &&
					   $1->query_leader() == $(who) :));
		"/d/guanwai/songhuajiang"->transfer(obs, "/d/guanwai/chuanchang");
		destruct(ob);
       		return -1;
	} else  
	{
		message_vision("������ü��$N˵������㣿��ôҲ��һ�����Ӱɣ�\n", who);
		return 0;
	}
}

void goto_songhua(object *obs)
{
	obs -= ({ 0 });
	message("vision", "\n���ܿ�ͣ���˰�����̧�ſ��������\n\n", obs);
	obs->move("/d/guanwai/chuanchang");
}

void unconcious()
{
	::die();
}
