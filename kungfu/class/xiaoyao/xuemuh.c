// xuemuh.c ѦĽ��
// shilling 97.2

inherit NPC;
inherit F_MASTER;

#include "xiaoyao.h"

int ask_me();
int ask_book();

void create()
{
	set_name("ѦĽ��", ({ "xue muhua", "xue" }));
	set("long", 
		"�����Ǻų������е���ҽ����ѦĽ������˵����ͨҽ����������������\n");
	set("gender", "����");
	set("title","��ң�ɡ����Ȱ��ѡ�");
	set("nickname","������Ѧ��ҽ");
	set("age", 50);
	set("class", "shaman");
	set("attitude", "peaceful");
	set("str", 25);
	set("int", 27);
	set("con", 25);
	set("dex", 25);

	set("inquiry", ([
		"����"       : (: ask_me :),
		"ҽ��"       : (: ask_book :),
		"��ң��ѧ"   : "��ң��ѧ��Ŷ����������Ҫ��������ľ����ɡ�",
		"������ľ�" : (: ask_book :),
		"�񶴺�ʯ��" : "����ѧ������ң��ѧ�Ϳ��������ˡ�",
		"��ת������" : "����ѧ������ң��ѧ�Ϳ��������ˡ�",
	]));

	set("max_qi", 1900);
	set("max_jing", 800);
	set("neili", 3100);
	set("max_neili", 3100);
	set("jiali", 60);
	set("combat_exp", 120000);

	set_skill("force", 90);
	set_skill("dodge", 90);
	set_skill("strike",90);
	set_skill("parry", 90);
	set_skill("feiyan-zoubi",80);
	set_skill("xiaoyao-xinfa", 80);
	set_skill("liuyang-zhang", 80);
	set_skill("medical", 150);
	set_skill("xiaoyao-qixue", 150);

	map_skill("strike", "liuyang-zhang");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("force", "xiaoyao-xinfa");

	prepare_skill("strike", "liuyang-zhang");

	create_family("��ң��", 3, "����");
	setup();

	set("xiaoyao_book", 1); 
	carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query_int() < 26)
	{
		command("sigh");
		command("say ��Ȼ��˵���ܲ�׾������... �ҿ��㻹���߰ɡ�");
		return;
	}

	command("say �ðɣ��Ҿ��������ˣ��Ժ�Ҫ��Ϊ��ң�ɳ�������");
	command("recruit " + ob->query("id"));
}

int ask_me()
{
	object ob;
	int time;

	ob = this_player();

	if (ob->query("family/family_name") != "��ң��")
	{
		 command("say �㲻�����ɵ��ӣ��Ҳ�����Ϊ�����ˡ�");
		return 1;
	}
	if ((int)ob->query("eff_qi") == (int)ob->query("max_qi"))
	{
		command("?" + ob->query("id"));     
		command("say ��û�����κ��˰���");
		return 1;
	} else
	if (ob->is_busy())
	{
		command("say �����п�����˵��");
		return 1;
	} else
	if (objectp(query_temp("recover")))
	{
		command("say û��������æô��");
		return 1;
	} else
	{
		time = 2 + random(3);
		message_vision("ѦĽ��ι$N����һ��ҩ�裬Ȼ����ϥ���£�˫������$N�ı��ġ�\n", ob);
		set_temp("recover", ob);
		remove_call_out("recover");
		call_out("recover", time, ob);
		ob->start_busy(time);
		return 1;
	}
}

int recover(object ob)
{
	delete_temp("recover");
	if (! objectp(ob))
		return 0;

	ob->set("eff_qi", (int)ob->query("max_qi"));
	ob->set("eff_jing", (int)ob->query("max_jing"));  
	message_vision("��Լ����һ�Ѳ��ʱ�ݣ�ѦĽ��������վ��������\n",ob);
	command("say ��������Ѿ�ȫ����,����������\n");
	 ob->interrupt_me(ob, 5);//���busy״̬
	return 1;
}

int ask_book()
{
	object me;
	object ob;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
	{
		command("say ����ʲô�ˣ������ҵ�ҽ���к�Ŀ�ģ�");
		return 1;
	}

	if ((int)me->query_skill("xiaoyao-qixue", 1) < 100)
	{
		command("say �����ң��ѧ���˽�̫ǳ������ѧ����"
			"��һЩ�Ҳ��ܰ��ر������㡣");
		return 1;
	}

	if (query("xiaoyao_book") < 1)
	{
		command("say ���ǿ�ϧ���������ˣ������Ѿ����ȥ�ˡ�");
		return 1;
	}

	add("xiaoyao_book", -1);
	ob = new("/clone/book/xiaoyao");
	message_vision("$n�ó�һ���������õĵ�С���ӵݸ�$N������"
		       "�������ţ������Ȿ�ˣ��úÿ�����\n",
		       me, this_object());
	ob->move(me, 1);
	return 1;
}
