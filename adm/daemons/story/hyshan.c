// story:hushan ����ɽ��˵

#include <ansi.h>

int give_gift(string name);

static mixed *story = ({
	"�׹Ǿ���ţ�磡",
	"ţħ������ɶ��",
	"�׹Ǿ���ţ�磬��ɵø�����������",
	"ţħ����˭�۸����ˣ�",
	"�׹Ǿ����������������Ǹ����...",
	"ţħ������ܣ��ĸ���ܣ�",
	"ţħ�����룺�Һ����кü��ٸ���ܰɣ���˵������һ������",
	"�׹Ǿ����ʵ��������Ǹ�����Ӱ���",
	"ţħ����ŭ����˵�����Ǻ��ӣ��ߣ����ȿӺ��Ҷ��ӣ������۸���ɩ��...",
	"ţħ���������ֵ���ƭ���ҵİŽ��ȣ����Ѿ����������ˣ�",
	"�׹Ǿ���ϲ���������Ҫ���ұ��𰡣��Ҹձ����۸���",
	"ţħ��������æ����������ϼ������֣�ȥ���㱨��",
	"......",
	(: give_gift, "niutou" :),
	"��˵ţħ���ɳ�ţͷ��(niutou guai)�����˻���ɽ��",
});

string prompt() { return HIM "���񻰴�˵��" NOR; }

void create()
{
	seteuid(getuid());
}

mixed query_story_message(int step)
{
	return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
	object ob;

	ob = new(CLASS_D("misc/") + name);
	if (! objectp(ob))
		return 0;

	NPC_D->place_npc(ob);
	if (! objectp(environment(ob)))
	{
		destruct(ob);
		return 0;
	}

	CHANNEL_D->do_channel(find_object(STORY_D), "sys",
			      ob->name() + "������" + environment(ob)->short() +
			      "(" + base_name(environment(ob)) + ")��");
	return 1;
}
