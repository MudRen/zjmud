// story:donghai ��������˵

#include <ansi.h>

int give_gift(string name);

static mixed *story = ({
	"��Ŵ��ɣ���սʤ��",
	"����գ�Ŷ��������ͷ�������ˣ��ϴ������͵�ϴ�赤����͵��ˣ�",
	"��Ŵ��ɣ��Ǹ���Ȼ����Ȼ��С�����ҵ����ʥ�Ĳ�ʹ��",
	"����գ��ޣ��Ǻã��Ǻã��һ��±������û���ء�",
	"��Ŵ��ɣ�����...����...",
	"����գ��ϼ���������ͷ��ô˵��",
	"��Ŵ��ɣ�...... �ܺã��ܺ�... ���ˣ��ϼ�������С�ɸ��ߴ�ʥ��׼������������ʢ���أ�",
	"����գ��ţ���������û�а��͡�������ҵ���ζ�����ҿ��Ǻܾ�û��Ʒ���ˡ�",
	"��Ŵ�����Ц������ֻ����������̫���������˴�ʥ�Ŀڸ��ˡ�",
	"������յ������ǣ�������ӻ�ĥĥ����ģ��ɴ�ŵ������������ˣ�",
	"��Ŵ���һ�ţ�����������ɣ����򲻿ɡ�",
	"�����Ц�������������˵˵�㻹�����ˣ���������ֻ��ûʲôζ����",
	"��Ŵ���ĨĨ�亹�������ҿ����͵����Ͳ������ʥ���Ĺ����ˣ������ˣ���һ����ټ���",
	"����գ��ã���ȥ�ɣ�",
	"......",
	"����հ��룺�����������ʢ�ỹ��һ��ʱ�䣬�������£��β��·�������ȴ��֪����Ⱥ����������ˡ�",
	(: give_gift, "sun" :),
	"��˵��սʤ�������(sun wukong)����˼���������˼䡣",
});

string prompt() { return HIM "���񻰴�˵��" NOR; }

// ÿ��һ��
int interval() { return 24 * 60 * 60; }

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
