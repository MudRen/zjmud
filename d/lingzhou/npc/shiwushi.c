// shiwushi.c

inherit NPC;


void create()
{
	set_name("ʯ����ʿ", ({ "wu shi", "shi" }));
	set("gender", "����");
	set("age", random(10) + 20);
	set("str", 25);
	set("dex", 16);
	set("long", "�����ػ����������ʯ����ʿ����Ȼ��׾������ȴʮ��ǿ��\n");
	set("combat_exp", 3000000);
	set("shen_type", 1);
	set("attitude", "aggressive");

	set_skill("unarmed", 380);
	set_skill("force", 380);
	set_skill("club", 380);
	set_skill("zhongping-qiang", 380);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	map_skill("club", "zhongping-qiang");
	set_temp("apply/attack", 300);
	set_temp("apply/armor", 350);
	set_temp("apply/damage", 150);

	set("neili", 10000); 
	set("max_neili", 10000);
	set("max_qi", 50000);
	set("max_jing", 50000);
	set("jiali", 30);

	setup();
	carry_object("/d/city/npc/obj/tiejia")->wear();
	carry_object("/clone/weapon/changqiang")->wield();
}

void die()
{
	object ob;
	int num,exp, pot, ww, sc;

	exp = random(400) + 200;
	pot = random(300) + 150;
	ww = random(30) + 30;
	sc = random(40) + 40;

	if ( objectp(ob = query_last_damage_from()) )
	{
		ob->add("combat_exp", exp);
		ob->add("potential", pot);
		ob->add("score", sc);
		ob->add("weiwang", ww);
		tell_object(ob,"ʯ����ʿ���һ�����ڵ��������һ����ʯ�����\n");
		num = time() - environment()->query("start_time");
		num = (900 - num)*2;
		if(num<0) num = 0;
		num += 1000;
		num -= 500*(ob->query("max_qi")-ob->query("qi"))/ob->query("max_qi");
		if(num>0&&mapp(ob->query("banghui")))
		{
			WARS_D->set_data("wangling/"+ob->query("banghui/name")+"/pot",WARS_D->query_data("wangling/"+ob->query("banghui/name")+"/pot")+num);
			tell_object(ob,"���ڽ����������������Ϊ����������"+num+"�㹱�ף�\n");
		}
		tell_object(ob, HIC "������" + exp +"�㾭�顢" + pot + "��Ǳ�ܡ�"+sc+"�㽭�������Լ�" + ww + "�㽭��������"NOR"\n");
	}
	destruct(this_object());
}
