// npc: /d/xingxiu/npc/bayi.c
// Jay 3/25/96

inherit NPC;
void create()
{
	set_name("����", ({ "ba yi", "bayi"}));
	set("gender", "����");
	set("age", 55);

	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	set_temp("apply/attack", 40);
	set_temp("apply/defense", 40);
	set_temp("apply/damage", 10);
	set("attitude","heroism");
	set("inquiry", ([
	   "����" : "�����Ű�����İ취���˺ö���ӣ���ʲôҲû"
		    "��������������Ҳû�ˡ�",
	   "������" : "�Ұ����ص��ҵĿ������ˡ�",
	]) );

	set("combat_exp", 25000);
	set("shen_type", -1);
	setup();
	set("chat_chance", 10);
	set("chat_msg", ({
	   "���������죺ɳ��һ���ӽ���һ���ӣ�����һ����ɳ��һ���ӡ�\n",
	   "����������󺰣���վ���ҵ�������ø���Ǯ!\n",
	   "����̾�˿��������Ƕ���ɳĮ�������ӣ���������?\n",
	}) );
	carry_object("/clone/cloth/wcloth")->wear();
}

int accept_object(object who, object ob)
{
	if (! ob->query("money_id"))
	{
		command("say �ⲻ��Ǯ������Ҹ�ʲô��");
		return 0;
	}

	message_vision("$NЦ���۾����е���һ�𣬵������ҿɾͲ���������\n",
		       who);
	who->set_temp("permit_pass/bayi", 1);
	destruct(ob);
	return 1;
}

