#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int do_skills(string arg);

void create()
{
	set_name("��������", ({ "dubi shenni", "dubi" }));
	set("gender", "Ů��");
	set("age", 44);
	set("str", 25);
	set("dex", 20);
	set("long", "����һλ����Ů�ᣬ���շ�����Ŀ��ǰ����\n"+
		"һֻ����տ���Ҳ�����Ƕ���һ�ۣ�������ˣ�\n"+
		"��Ȼ�ڲ�ס�����˵ķ�ɡ�\n");
	set("combat_exp", 200000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("whip", 150);
	set_skill("force", 90);
	set_skill("unarmed", 90);
	set_skill("dodge", 150);
	set_skill("parry", 90);
	set_skill("qiufeng-chenfa", 150);
	set_skill("shenxing-baibian", 150);
	map_skill("whip", "qiufeng-chenfa");
	map_skill("parry", "qiufeng-chenfa");
	map_skill("dodge", "shenxing-baibian");

	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/armor", 40);
	set_temp("apply/damage", 100);
	set("neili", 1500); 
	set("max_neili", 1500);
	set("jiali", 100);
	set("inquiry", ([
		"����" : "����̾��һ������˵���������ҵĵ�����ӣ�\n"
			 "�˳���ͦ��������ֻ��ϧ��ΤС��ƭȥ�ˡ�\n",
	]) );
	setup();
	carry_object("/d/beijing/npc/obj/fuchen")->wield();
	carry_object("/d/beijing/npc/obj/cloth4")->wear();
	add_money("silver", 2);
}

void init()
{
	::init();
	if (this_player()->query("id") == "la ma")
	{
		delete_temp("saved_by_others");
	} else
	if (interactive(this_player()))
	{
		remove_call_out("greeting");
		call_out("greeting", 1, this_player());
	}
}

int recognize_apprentice(object ob)
{
	if (! ob->query("can_learn/dubi/shenxing-baibian"))
	{
		message_vision("$Nҡ��ҡͷ��\n",this_object());
		command("say �����ز���ʶ��Ϊʲô��һ��Ҫ�����أ�"); 
		return -1;
	}
	return 1;       
}

void greeting(object ob)
{
	object man;
	
	if (! ob || environment(ob) != environment()) return;
	    
	man = this_object();
	if (! present("la ma"))
	{
		message_vision(HIC "$N̤��������ֻ������ʬ���£�һ��Ů"
			       "�ᴭϢ��ֹ��"NOR"\n", ob);	       
		if (! query_temp("saved_by_others"))
		{
			set_temp("saved_by_others", 1);
			ob->set("can_learn/dubi/shenxing-baibian", 1);
			message_vision("\n����Ů���$N˵��������л��λ" +
				       RANK_D->query_respect(ob)+
				       "�ε�������ƶ��м�����������Ϊ����\n"
				       "������һ�����аٱ���������Ըѧ��ƶ"
				       "�ᶨ�������ڡ���\n", ob);
			if (ob->query("weiwang") < 60)
			{
				ob->add("weiwang", 10);
				message_vision(HIC "$N�Ľ�����������ˣ�"NOR"\n",ob);
				return ;
			}
			return;
		}
		message_vision(HIC "����Ů���$N΢΢һЦ��"NOR"\n",ob);
	}
}

