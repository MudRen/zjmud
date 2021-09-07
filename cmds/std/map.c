// map.c

#include <ansi.h>

inherit F_CLEAN_UP;

int map_view(object me, string arg);
int map_rumor(object me, string arg);

void create() 
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	string here, name;
	object env;
	string *mapped;
	int lvl;
	int exp, pot, score;
	int pot_limit;
	string msg;
	mixed prompt;
	if (! arg)
		return notify_fail("��ʽ��map here | rumor | view | all | <�ص�> | <����>��\n");

	if (arg == "rumor")
		return map_rumor(me, arg);

	if (arg == "world")
	{
		write(ZJMAPTXT+replace_string(color_filter(read_file("/help/mapall")),"\n",ZJBR)+"\n");
		return 1;
	}

	if (arg != "here")
		return map_view(me, arg);
/*
	if (! me->query("out_family"))
	{
		write("�����ڻ�û�д�ʦ�������쵽��ͼ�ᡣ\n");
		return 1;
	}
*/
	// ���ĵ�ǰ�Ļ���
	env = environment(me);
	name = env->short();
	if (! stringp(here = env->query("outdoors")))
	{
		write("ֻ���ڻ�����б�Ҫ���Ƶ�ͼ��\n");
		return 1;
	}

	if (! stringp(name) || clonep(env))
	{
		write("������һ�����صĵط������޷��ж����ķ�λ��\n");
		return 1;
	}

	if (me->query("map_all"))
	{
		write("���Ѿ�����˵�ͼȫ����û�б�Ҫ�ٻ��Ƶ�ͼ�ˡ�\n");
		return 1;
	}

	if (me->is_busy())
	{
		write("��������æ��û��ʱ����Ƶ�ͼ��\n");
		return 1;
	}

	// �����Ѿ����ƹ��ĵ�ͼ
	mapped = me->query("map/" + here);
	if (! arrayp(mapped)) mapped = ({ });
	if (member_array(name, mapped) != -1)
	{
		write("���Ѿ����ƹ��⸽���ĵ�ͼ�ˣ�û�б�Ҫ���ظ��ˡ�\n");
		return 1;
	}

	if (! MAP_D->been_known(here))
	{
		write("���������ûʲô�û��ġ�\n");
		return 1;
	}

	if (prompt = env->query("no_map"))
	{
		if (stringp(prompt))
			write(prompt);
		else
			write("�㿴�˰��죬Ҳû��Ū��������ĵ��Ρ�\n");
		return 1;
	}

	if (me->query("jing") < 50)
	{
		write("��ľ��񲻼ѣ��޷�����ȫ���ע�Ļ��Ƶ�ͼ��\n");
		return 1;
	}

	// ���ľ�
	me->receive_damage("jing", 20 + random(30));

	if ((lvl = me->query_skill("drawing", 1)) < 30)
	{
		write("����ֽ��ͿĨ��һ��������Լ�����������ʲô������\n");
		write("����������ǧ�ﴫ������Ļ滭���ɲ���30��������������ݱ���³��ѧϰ����ܡ�\n");
		return 1;
	}

	message("vision", me->name() + "̧ͷ���˿����ܣ���ͷ����ϸϸ�Ļ�����ʲô��\n", environment(me), ({ me }));
	tell_object(me, "�㾫�ĵĻ�����" + name + "�����ĵ��Ρ�\n");

	mapped += ({ name });
	me->set("map/" + here, mapped);

	//me->start_busy(1 + random(3));

	// ���㽱��
	if (lvl > 200)
		lvl = (lvl - 200) / 4 + 150;
	else
	if (lvl > 100)
		lvl = (lvl - 100) / 2 + 100;

	exp = 100 + random(lvl);
	pot = 20 + random((lvl - 20) / 5);
	score = 1+random(3);
	pot_limit = me->query_potential_limit() - me->query("potential");
	if (pot_limit < 0)
		pot_limit = 0;
	if (pot >= pot_limit)
		pot = pot_limit;

	msg = "������" + chinese_number(exp) + "�㾭��";
	if (pot > 0)
		msg += "��" + chinese_number(pot) + "��Ǳ��";

	if (score)
		msg += "��ͨ�����������ۻ���" + chinese_number(score) + "�㽭������";

	// ������Ч
	write(HIC + msg + "��"NOR"\n");
	me->add("combat_exp", exp);
	me->add("potential", pot);
	me->add("score", score);

	return 1;
}

// �鿴�Ѿ����Ʋ��ֵĵ�ͼ
int map_view(object me, string arg)
{
	mapping mapped;
	mapping rumor;
	string outdoors;
	string *shorts;
	string result;
	string key;

	if (! me->query("out_family"))
	{
		write(ZJMAPTXT+replace_string(MAP_D->marked_map(environment(me)),"\n",ZJBR)+"\n");
		return 1;
	}

	mapped = me->query("map");
	if (! me->query("map_all") && ! mapp(mapped))
	{
		write(ZJMAPTXT+replace_string(MAP_D->marked_map(environment(me)),"\n",ZJBR)+"\n");
		return 1;
	}

	if (me->is_busy())
	{
		write("��������æ��û���鿴��ͼ��\n");
		return 1;
	}

	message_vision("$N�ó�һ�����������������ķ�������������\n", me);
	me->start_busy(1);

	// �쿴�Ƿ��Ķ�����
	if (mapp(rumor = me->query("rumor")) && member_array(arg, keys(rumor)) != -1)
	{
		write("�㷭����ͼ��ĺ��棬��ϸ�Ķ��йء�" + arg + "���ļ��ء�\n" WHT + rumor[arg]->query_detail(arg) + NOR);
		return 1;
	}

	// �Ƿ��ǲ쿴���ص�ͼ��
	if (arg == "view" || me->query("map_all"))
	{
		write(ZJMAPTXT+replace_string(MAP_D->marked_map(environment(me)),"\n",ZJBR)+"\n");
		me->start_busy(2);
		return 1;
	}

	// �ж��Ƿ������ĵ�ͼ����
	foreach (key in keys(mapped))
		if (MAP_D->query_map_short(key) == arg)
		{
			// ���������֣�ת����Ӣ��ID
			arg = key;
			break;
		}

	// �����ⷽ��ĵ�ͼ
	if (arrayp(shorts = mapped[arg]))
	{
		result = MAP_D->query_maps(arg);
		foreach (key in shorts)
		{
			reset_eval_cost();
			if (! stringp(key))
				continue;
			result = MAP_D->mark_map(result, key);
		}
		result = replace_string(result, "@R", WHT);
		result = replace_string(result, "@N", NOR);
		me->start_more(MAP_D->query_map_short(arg) + "�ĵ�ͼ��Ϣ��\n" + result);
		me->start_busy(2);
		return 1;
	}

	if (arg != "all")
	{
		write("��ĵ�ͼ���в�û���й� " + arg + " ����Ϣ����\n");
		return 1;
	}

	outdoors = environment(me)->query("outdoors");
	if (stringp(outdoors))
		result = "��������" + MAP_D->query_map_short(outdoors) + "���ڡ�\n";

	result = "Ŀǰ���Ѿ�������������Щ�ط��ĵ�ͼ��\n";
	foreach (key in keys(mapped))
		result += MAP_D->query_map_short(key) + "(" HIY + key + NOR ")\n";
	write(result);
	return 1;
}

int map_rumor(object me, string arg)
{
	mapping rumor;
	string msg;

	if (! mapp(rumor = me->query("rumor")))
	{
		write("�����ڲ�û�м�¼�κδ���Ȥ�¡�\n");
		return 1;
	}

	msg = "��Ŀǰ�������й�" + implode(keys(rumor), "��") + "�Ĵ��š�\n";
	msg = sort_string(msg, 60);
	write(msg);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : map here | rumor | all | view | <�ص�> | <����>

������������˵�ͼ�ᣬ�Ϳ���ʹ������������Ƹ����ĵ�ͼ����Ȼ
��������ڻ��⣬���Ҿ߱���һ���Ļ滭���ɲſ��ԡ����Ƶ�ͼ����
������ľ��顢Ǳ�ܲ����۽���������

ʹ�� map all ���Բ鿴�������Ѿ���������Щ�ط��ĵ�ͼ�� �����
ָ���˾���ĵط�������Բ鿴�õص�ĵ�ͼ���������

������ڻ��⣬�����ʹ�� map view ����鿴�����ڵĵص㡣

map rumor ���Բ�����Ŀǰ��¼�ĸ������ţ�ʹ�� map <����> ���
�Բ鿴�������ݡ�
HELP );
    return 1;
}
