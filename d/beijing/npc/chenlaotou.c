// chen.c

inherit KNOWER;

void create()
{
	set_name("����ͷ", ({ "chen laotou", "chen", "laotou" }) );
	 set("title", "�͵��ϰ�");
	set("gender", "����" );
	set("age", 32);
	set("long",
	      "һ�������Ѯ��С��ͷ�����������С�͵���ϰ塣\n");
	set("shen_type", 1);
	set("combat_exp", 3000);
	set("str", 10);
	set("dex", 10);
	set("con", 10);
	set("int", 10);
	set("attitude", "peaceful");
	set_skill("dodge", 10);
	set_skill("unarmed", 10);
	set("chat_chance", 1);
	set("chat_msg", ({
		"����ͷ��Ц�Ŷ���˵������λ�͹٣����ǶԲ�ס��С���Ѿ������ˡ�\n",
		"����ͷһ�ߺ���С��һ������Ĩ������������\n",
		"����ͷһ�����ֹ���������Ҳ�û����ˡ�\n",
	}) );       

	setup();
	carry_object("/d/beijing/npc/obj/cloth")->wear();
	add_money("silver", 5);
}
