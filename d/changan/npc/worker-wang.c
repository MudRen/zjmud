// worker-liu.c

inherit NPC;

#include <ansi.h>

// ���յĻ���
#define CHECK_GOODS     "stone"

void create()
{
	set_name("��ʯ��", ({ "wang shijiang", "wang" }) );
	set("title", HIY "�����" NOR);
	set("gender", "����" );
	set("age", 48);
	set("str", 35);
	set("long", @LONG
һ��������ɣ���Ͻ��ˣ�����ȥ��Ȼǿ׳������������͸¶������
�����ϡ�
LONG);
	set("attitude", "friendly");

	setup();

	carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
	set_heart_beat(1);
}

int filter_ob(object ob)
{
	object owner;

	if (! ob->is_transport())
		return 0;

	owner = ob->query_owner();
	if (! objectp(owner))
		// �ó�����
		return 0;

	if (environment(owner) != environment())
		// ���˲���
		return 0;

	if (ob->query_temp("goods/id") != CHECK_GOODS)
		// û��װ��ʯ��
		return 0;

	if (ob->query_temp("goods/amount") < 1)
		// û�л�
		return 0;

	return 1;
}

void heart_beat()
{
	object *obs;
	object ob;
	object owner;
	string startroom;
	int amount;
	mapping job;
	mapping goods;
	object bonus;

	::heart_beat();
	if (! environment())
		return;

	if (! stringp(startroom = query("startroom")) ||
	    find_object(startroom) != environment())
		// ���ڳ����ص�
		return;

	obs = all_inventory(environment());
	obs = filter_array(obs, (: filter_ob :));
	if (sizeof(obs) < 1)
	{
		// û�е�����ʵĳ�����ֹͣ����
		set_heart_beat(0);
		return;
	}

	// �����˺��ʵĳ���
	ob = obs[0];
	owner = ob->query_owner();
	message_vision("$N����$nѺ��������������ͷ��������"
		       "�ã��ܺã���ж������ɣ���\n",
		       this_object(), owner);
	tell_object(owner, "��ж��" + ob->query_temp("goods/name") +
		    "����" + ob->name() + "����ѧͽ���ߡ�\n");

	// ж��ʯ��
	goods = ob->query_temp("goods");
	amount = goods["amount"];
	environment()->improve_product_amount(goods["id"], amount);

	// ���뽱��
	MONEY_D->pay_player(owner, amount / 100 * 300);
	tell_object(owner, "���쵽��һЩ��Ǯ��\n");
	if (ob->query_temp("job/owner") == owner)
	{
		// ����Ǳ�����Ĺ�������ý���
		QUEST_D->bonus(owner, ([ "exp" : 20 + random(20),
					 "pot" : 15 + random(10),
					 "score" : 3 + random(5),
					 "prompt" : "ͨ�����Ѻ��" + goods["name"] + HIG ]));

		// ȥ�����������������Ϣ
		owner->delete("job/" + ob->query_temp("job/info"));
	}
	destruct(ob);

	if (sizeof(obs) < 2)
	{
		// �Ѿ�������ϣ�û���µĳ������ֹͣ����
		set_heart_beat(0);
	}
}
