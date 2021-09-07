// NPC: cheng.c ������
// Date: Mar. 1 2002 Modify by Pound

#include <ansi.h>

inherit NPC;

string ask_me();
int    ask_shu();
int    ask_candle();
int    ask_lianzhi();

void create()
{
	set_name("������", ({ "cheng lingsu", "cheng" }));
	set("gender", "Ů��");
	set("age", 24);
	set("long", @long
������ȥ˫ü��������֪����ʲô���£�������òƽƽ���������ڡ�
�����С�����Ŵֲ�������
long);
	set("attitude", "peaceful");
	set("str", 22);
	set("int", 35);
	set("con", 31);
	set("dex", 27);
	set("chat_chance", 10);
	set("chat_msg", ({
		"�����ذ�����̾�˿�����\n",
	}));

	set("qi", 2500);
	set("max_qi", 2500);
	set("jing", 1200);
	set("max_jing", 1200);
	set("neili", 2800);
	set("max_neili", 2800);
	set("jiali", 40);
	set("combat_exp", 400000);
     
	set_skill("force", 150);
	set_skill("poison", 270);
	set_skill("dispel-poison", 270);
	set_skill("medical", 270);
	set_skill("yaowang-miaoshu", 270);

	set("inquiry",([
		"���"     : "��...��...\n",
		"Ԭ����"   : "��...��������ʲô��\n",
		"ҩ����ƪ" : (: ask_shu :), 
		"���ĺ���" : "�Һ������ĺ���������ֲ���������ϻ���˭�ܵ�ƽ����\n",
		"����" : (: ask_me :),
		"����" : (: ask_candle :),
		"��������" : (: ask_lianzhi :),
	]));

	set("book_count", 1);

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("family/family_name") != "�������")
	{
		command("say ����˭������ʲô��");
		return -1;
	}

	if (skill != "poison" && skill != "dispel-poison" &&
	    skill != "medical" && skill != "yaowang-miaoshu")
	{
		command("say ��ֻ�ᶾ����ҽ��������Ҿ�û���ӽ�������");
		return -1;
	}

	if ((int)me->query("shen") < 0)
	{
		command("sigh");
		command("say ����������а·���ҿɲ��ܽ��㶾����");
		return -1;
	}

	if (! me->query_temp("can_learn/cheng/poison"))
	{
		me->set_temp("can_learn/cheng/poison", 1);
		command("say ���ں�쳵������ϣ��Ҿͽ���һ�㱾�°ɣ����Ҫ����Ϊ֮��");
		return 1;
	}

	return 1;
}

int ask_shu()
{
	object me;
	object ob;

	me = this_player();
	if (me->query("family/family_name") != "�������")
	{
		command("say ����˭�����ɶ��");
		return -1;
	}

	if (me->query_skill("yaowang-miaoshu", 1) < 50)
	{
		command("say ����ҩ���˽��̫�٣������Ⱥúú���ѧѧ�ɡ�");
		return -1;
	}

	if (query("book_count") < 1)
	{
		command("say û�ˣ��ս��ߡ�");
		return -1;
	}

	message_vision("$N�ͳ�һ��С���ӣ��ݸ�$n����������"
		       "����ͺú��о��ɣ��ɱ���̤�ˡ���\n",
		       this_object(), me);
	ob = new("/clone/book/yaowang");
	ob->move(me, 1);
	add("book_count", -1);
	return 1;
}

int ask_candle()
{
	object me;
	object ob;
	int count;

	me = this_player();
	if (me->query("family/family_name") != "�������")
	{
		command("say ����˭�����ɶ��");
		return -1;
	}

	if (present("haitang candle", me))
	{
		command("say �����ϲ�����һ��ô��ǧ��Ҫ����ʹ��ѽ��");
		return -1;
	}

	if (! me->query("yaowang/makehaitang"))
	{
		command("say ���ĺ��Ķ��Լ�ǿ�����Ƴ������Ժ����ɱ��������֮�С�");
		me->set_temp("yaowang/candle/ask", 1); // ������ʱ�������ڳ����ؽ������ĺ���
		return -1;
	}

	count = me->query("yaowang/makehaitang"); 
	message_vision("$N�ӻ����ͳ�һ��ϸС�����򣬵ݸ�$n����������"
		       "���������ȼ�����ɱ�������Σ���֮��֮����\n",
		       this_object(), me);
	ob = new("/clone/herb/candle");
	ob->move(me, 1);
	me->set("yaowang/candle/using", count); // �����ʹ�õĴ���
	tell_object(me, "���ĺ���������ʹ��" + count + "�Ρ�\n");
	me->delete("yaowang/makehaitang");
	return 1;
}

int ask_lianzhi()
{
	object who, me, ob;
	int count;

	me = this_object();
	who = this_player();
	if(objectp(ob = present("qixin haitang", who)) && who->query_temp("yaowang/candle/ask")) 
	{
	    count = 4 - who->query("yaowang/qxht/using");

	    if (count < 2)
	    {
		command("hmm");
		command("say ���ĺ��Ķ��챻�����������Ѿ������������������ˡ�");
		return 0;
	    }

	    who->set("yaowang/makehaitang", count);
	    destruct(ob);
	    who->delete("yaowang/qxht");
	    message_vision("$n����$Nһ�����ĺ��ġ�\n", me, who);
	    command("say �����ȥ����������������ȥæ�ɣ�����ʱ����������Ҫ��");
	    message_vision("$N����ææ���뿪�ˡ�\n", me);
	    destruct(me);
	    return 1;
	}
	return 0;
}

string ask_me()
{
	object me;
	me = this_player();

	if (me->query("family/family_name") != "�������")
	{
	    command("en");
	    return "���ʵ�����̫���˰ɡ�\n";
	}

// ��С˵��д���Ȱ�æ��ЩҨ�ཽ���Ĺ������̲Ż�����øУ��п��ܸ��������ܡ�
	if (me->query_temp("yaowang/jiao") < 30)
	{
	    return "ʦ�����Ӻ�����������ĺ��ĵ����ӣ�������ʦ��������\n";
	}
	else
	{    
	    if (me->query_skill("yaowang-miaoshu", 1) < 200)
	    {
		return ("�����ĺ��ĵļ�����ֲ���������Ϊ�����������\n"); 
	    }
	    command("nod"); 
	    me->set_temp("yaowang/zhongzi", 1);
	    return "�㵽������ʦ�����µ����ĺ���������ֲ�������ǵò�Ҫ�������ˣ�\n";
	}
}

void reset()
{
	set("book_count", 1);
}