//baobiao.c

inherit NPC;

void create()
{
	set_name("Ⱥ��¥����", ({ "bao biao","baobiao" }));
	set("gender", "����");
	set("age", random(10) + 20);
	set("str", 25);
	set("con", 25);
	set("spi", 25);
	set("dex", 25);
	set("int", 25);
	set("shen_type", -1);
	set("long", "��ɱ�����ڣ�����Ⱥ��¥����Ů�˵İ�ȫ��\n");
	set("combat_exp", 100000);
	set("class", "fighter");
	set("attitude", "herosim");
	set_skill("unarmed", 70);
	set_skill("force", 70);
	set_skill("sword", 70);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set("max_qi", 700);
	set("max_jing", 700);
	set("max_neili", 600);
	set("neili",600);
	set("jiali", 40);
	set("max_jingli", 600);
	set("jingli", 600);

	setup();
	carry_object(__DIR__"obj/sword")->wield();
	carry_object(__DIR__"obj/zhanjia")->wear();
}

int accept_fight(object me)
{
	message_vision("Ⱥ��¥���ڶ�$N�ȵ����ǲ�����������\n\n", me);
	return 0;
}

int heal_up()
{
	if (environment() && !is_fighting()) 
	{
		call_out("leave", 1);
		return 1;
	}
	return ::heal_up() + 1;
}

void leave()
{
	object stone;
	this_object()->add("time", 1);
	if ((int)this_object()->query("time") >= 3) 
	{
		message("vision", name() + "�ٺ�һЦ:������Ҫ��ȥ"
			"˯���ˣ���������Ⱥ��¥���¾ͽ��ң���\n",
			environment());
		destruct(this_object());
	}
	return;
}
